#include "gdt.h"
#include "idt.h"
#include "minilib.h"

extern int app_main(int a, int b);
extern int multiplication(int a,int b);
void empty_irq(int_regs_t *r) {
}

/* multiboot entry-point with datastructure as arg. */
void main(unsigned int * mboot_info)
{
    /* clear the screen */
    clear_screen();
    puts("Early boot.\n");

    /* Initialize the memory */
    puts("\t-> Setting up the GDT... ");
    gdt_init_default();
    puts("OK\n");

    /* Initializa the Interrupt Descriptor Table */
    puts("\t-> Setting up the IDT... ");
    setup_idt();
    puts("OK\n");

    puts("\n\n");

    /* Installs two empty handlers for the timer (0) and the keyboard (1) */
    idt_setup_handler(0, empty_irq);
    idt_setup_handler(1, empty_irq);

    /* Enables interrupts */
    __asm volatile("sti");

    /* minimal setup done ! */
    //on effectue les appels imbriques puis les appels successifs de fonctions
    int value_1 = 2;
    int value_2 = 5;
    int result1 = app_main(value_1, value_2);
    int result2 = multiplication(value_1, value_2);
    puts("Going idle\n");
    for(;;) ; /* nothing more to do... really nothing ! */
}
