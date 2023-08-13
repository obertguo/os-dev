#include "paging.h"
#include "../../drivers/screen.h"

// A page directory table (PDT) has 1024 entries, and each are 4 bytes
// Each entry in a PT stores a pointer to a 4Kib page table (PT)
// Also, each entry in a PD has bits for controlling access protection 
// and caching 

// Also, it is important that the PDT is aligned on a 4 Kib boundary
unsigned int page_directory_table[1024] __attribute__((aligned (4096))) = {0};

// In each page table (PT), there are also 1024 4 byte entries and is VERY 
// similar to PD entries. It is also aligned on a 4 Kib boundary.
// Each entry in the PT maps to an address representing 4 Kib block of memory.  

// Each page is 4 Kib (4096 bytes) and since a page table (PT) has 1024 entries,
// then we this first page table maps out 4096 bytes * 1024 = 4 MB of memory
// If we initialize more PTs for each of the entries in the PD, then we can have
// 4MB * 1024 = 4GB of memory mapped out for the full 32-bit address space.
unsigned int indentity_page_table[1024] __attribute__((aligned (4096))) = {0};

unsigned int kernel_higher_half_page_table[1024] __attribute__((aligned (4096))) = {0};

void initialize_page_directory() {
    for (int i = 0; i < 1024; ++i) {
        page_directory_table[i] = PDT_INITIAL_ENTRY;
    }
}

void initialize_identity_page_table() {

     for (int i = 0; i < 1024; ++i) {
        // A page is 4096 bytes, so we do this to get the physical address
        // of each page
        const int physical_address = i * 4096;

        // Since the last 12 bits are zeroed out by the MMU in the translation
        // we will also set the attributes for the page entry
        const int page_table_entry = physical_address | PTE_ATTRIBUTES;        

        indentity_page_table[i] = page_table_entry;
    }

    page_directory_table[0] = ((unsigned int) (&indentity_page_table)) | PTE_ATTRIBUTES;
}

void initialize_kernel_higher_half_page_table() {

     for (int i = 0; i < 1024; ++i) {
        // A page is 4096 bytes, so we do this to get the physical address
        // of each page
        const int physical_address = i * 4096;

        // Since the last 12 bits are zeroed out by the MMU in the translation
        // we will also set the attributes for the page entry
        const int page_table_entry = physical_address | PTE_ATTRIBUTES;        

        kernel_higher_half_page_table[i] = page_table_entry;
    }

    const int PD_entry = KERNEL_HIGHER_HALF_VIRTUAL_ADDR / (1024 * 4096); //entry 768 in PDT
    page_directory_table[PD_entry] = ((unsigned int) (&kernel_higher_half_page_table)) | PTE_ATTRIBUTES;
}

void load_page_directory_table(unsigned int *pdt) {
    __asm__ volatile ("mov %%eax, %%cr3" : : "a" (&page_directory_table));
}

void enable_paging() {
    unsigned int cr0 = 0;

     __asm__ volatile ("mov %%cr0, %%eax" : "=a"  (cr0));
    unsigned int cr0_set_page_enable_bit = cr0 | 0x80000000;

    __asm__ volatile ("mov %%eax, %%cr0" : : "a"  (cr0_set_page_enable_bit));
}

void setup_identity_paging() {
    initialize_identity_page_table();

    load_page_directory_table(&page_directory_table);
    enable_paging();

    print("Identity paging enabled for the first 4MB of memory!");
}

void setup_kernel_higher_half_paging() {
    //initialize_page_table();

    load_page_directory_table(&page_directory_table);
    enable_paging();

    print("Higher half kernel enabled");
}