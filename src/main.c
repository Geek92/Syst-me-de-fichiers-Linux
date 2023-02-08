#include "gdt.h"
#include "idt.h"
#include "minilib.h"

//extern void app_main();
extern void app_main2();
extern void app_main3();

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
      //swtich to context
      //app_main();
      //yield
      //app_main2();
      //round_robbind
      app_main3();
    puts("Going idle\n");
    for(;;) ; /* nothing more to do... really nothing ! */
}
