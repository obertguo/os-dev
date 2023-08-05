#include "../isrs/isrs.h"
#include "../idt/idt.h"
#include "../../util.h"
#include "irq.h"
#include "../../../drivers/screen.h"

extern void isr32();
extern void isr33();
extern void isr34();
extern void isr35();
extern void isr36();
extern void isr37();
extern void isr38();
extern void isr39();
extern void isr40();
extern void isr41();
extern void isr42();
extern void isr43();
extern void isr44();
extern void isr45();
extern void isr46();
extern void isr47();

void *isr_routines_irq[] = {
    isr32, isr33, isr34, isr35, isr36, isr37, isr38, isr39,
    isr40, isr41, isr42, isr43, isr44, isr45, isr46, isr47
};

//  Array of function pointers for our custom
//      interrupt handlers for PIC slave and master - all null pointers for now
void *irq_routines[] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

// irq_install_handler(irq, handler) installs a specific handler
//      for the corresponding IRQ number (without the IDT offset)
// Requires: 0 <= irq < 16, and handler is a valid function pointer
void irq_install_handler(unsigned int irq, 
    void *(handler)(const struct registers *r)) {
    irq_routines[irq] = handler;
}

// irq_uninstall_handler(irq) uninstalls the handler for the corresponding
//      IRQ number (without the IDT offset)
// requires: 0 <= irq < 16
void irq_uninstall_handler(unsigned int irq) {
    irq_routines[irq] = 0;
}

// irq_install() remaps IRQs raised by PICs and installs the IRQ into the IDT
void irq_install() {
    // We need to remap IRQs issued from master and slave PICs to
    // entries 32 to 47 in the IDT. 
    //
    // Since historically, the master PIC sends IRQs 0 to 7
    // which is remapped to entry 8 to 15 in the IDT, and the slave PIC sends
    // IRQs 8 to 15 which is remapped to entry 0x70 to 0x7f in the IDT 
    //
    // This is fine in 16 bit real mode, but in 32 bit PM,
    // if the master PIC issues IRQ 0 for example, that invokes the 8th entry 
    // in the IDT, which is the Double Fault Exception! We do not want that!

    // https://wiki.osdev.org/8259_PIC
    // https://wiki.osdev.org/Talk:8259_PIC
    // http://www.osdever.net/bkerndev/Docs/irqs.htm

    // save PIC data registers
    unsigned char master_data = port_byte_in(PIC_MASTER_DATA);
    unsigned char slave_data = port_byte_in(PIC_SLAVE_DATA);

    // The initialization command makes the PIC wait for 3 extra
    // initialization words on the data port
    // These 3 bytes give the PIC the vector offset from the IDT,
    // tell the PIC how it is wired to master/slaves, and 
    // additional info about the environment

    port_byte_out(PIC_MASTER_CMD, PIC_INITIALIZE_CMD);
    port_byte_out(PIC_MASTER_DATA, PIC_MASTER_IDT_OFFSET);
    port_byte_out(PIC_MASTER_DATA, PIC_MASTER_IDENTITY);
    port_byte_out(PIC_MASTER_DATA, PIC_8086_MODE);
    port_byte_out(PIC_MASTER_DATA, master_data);

    port_byte_out(PIC_SLAVE_CMD, PIC_INITIALIZE_CMD);
    port_byte_out(PIC_SLAVE_DATA, PIC_SLAVE_IDT_OFFSET);
    port_byte_out(PIC_SLAVE_DATA, PIC_SLAVE_IDENTITY);
    port_byte_out(PIC_SLAVE_DATA, PIC_8086_MODE);
    port_byte_out(PIC_SLAVE_DATA, slave_data);

    for (unsigned char i = 32; i < 48; ++i) {
        idt_set_gate(i, isr_routines_irq[i - 32], KERNEL_CODE_SEGMENT, FLAGS);
    }
}

// irq_handler(r) is eventually called by the corresponding ISR assembly routine  
//      for that IRQ number to call our defined (if it exists) handler for 
//      the PIC interrupt number.
//  Requires: r is a valid pointer to the stack where all the registers 
//              are pushed.
void irq_handler(const struct registers *r) {

    // Initilize handler pointer
    void (*handler)(const struct registers *) = 0;

    // update handler pointer based on IRQ number
    // recall that IRQ number being retrieved is from 32 to 47
    // so we offset that by 32 to determine which handler to get in our array
    handler = irq_routines[r->int_no - 32];

    // check if handler is valid
    if (handler) {
        handler(r);

        // do something here if no handler is implemented yet...
    } else {
        clear();
        print("IRQ handler is not implemented!");
    }

    // If IRQ that is called is invoked by the slave PIC (IRQ 40 to 47)
    // then we need to send EOI (end of interrupt) to the slave PIC
    if (r->int_no > 39) {
        port_byte_out(PIC_SLAVE_CMD, PIC_EOI_CMD);
    } 

    // In either case, the master PIC also needs to be sent EOI
    port_byte_out(PIC_MASTER_CMD, PIC_EOI_CMD);
}