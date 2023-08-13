#ifndef PAGING_H
#define PAGING_H

// This sets the following flag to the pages:
//      Page Size: 0 - Indicates 4 Kib page size
//      Accessed: 0 - indicated PDT/PTE is not read during virtual 
//          adddress translation. (Needs to be cleared by OS)
//      Page Cache Disable: 0 - indicates page will be cached
//      Page Write Through: 0 - write back is enabled
//      User/Supervisor: 0 - only kernel-mode/supervisor can access
//      Read/Write: 1 - Can be both read and written 
//      Present: 0 - The page table is not present

// A page is "not present" when it's not intended to be used 
// If the MMU finds a page "not present," a page fault interrupt occurs
// and can be useful for techniques like Lazy Loading or if a page is swapped 
// to disk.
#define PDT_INITIAL_ENTRY 0x00000002

// Last 3 bits sets the following flags for the PDE
//      User/Supervisor: 0 - only kernel-mode/supervisor can access
//      Read/Write: 1 - Can be both read and written 
//      Present: 1 - The page entry is present
#define PTE_ATTRIBUTES 0x00000003

#define KERNEL_HIGHER_HALF_VIRTUAL_ADDR 0xC0000000


void setup_identity_paging();
void initialize_page_directory();


#endif