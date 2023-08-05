// https://wiki.osdev.org/8259_PIC
// https://wiki.osdev.org/Talk:8259_PIC
// http://www.osdever.net/bkerndev/Docs/irqs.htm

#ifndef IRQ_H
#define IRQ_H

#define PIC_MASTER_CMD 0x20         // IO port address
#define PIC_MASTER_DATA 0x21        // IO port address

#define PIC_SLAVE_CMD 0xA0          // IO port address
#define PIC_SLAVE_DATA 0xA1         // IO port address

#define PIC_INITIALIZE_CMD 0x11
#define PIC_EOI_CMD 0x20

#define PIC_MASTER_IDT_OFFSET 0x20  // entry 32 in IDT
#define PIC_SLAVE_IDT_OFFSET 0x28   // entry 40 in IDT

#define PIC_MASTER_IDENTITY 4       // needed to inform PIC master that there 
                                    // is a PIC slave
#define PIC_SLAVE_IDENTITY  2       // needed to inform PIC slave that there is
                                    // a PIC master
#define PIC_8086_MODE       0x01    // PICs need to bet set into 8086 mode
                                    // for for x86 CPUs. PICs by default 
                                    // use 8080 mode

// irq_install_handler(irq, handler) installs a specific handler
//      for the corresponding IRQ number (without the IDT offset)
// Requires: 0 <= irq < 16, and handler is a valid function pointer
void irq_install_handler(unsigned int irq, 
                        void *(handler)(const struct registers *r));

// irq_uninstall_handler(irq) uninstalls the handler for the corresponding
//      IRQ number (without the IDT offset)
// requires: 0 <= irq < 16
void irq_uninstall_handler(unsigned int irq);

// irq_install() remaps IRQs raised by PICs and installs the IRQ into the IDT
void irq_install();

#endif