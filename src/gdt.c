#include "gdt.h"
#include <stdint.h>

#define GDT_ENTRIES 3

struct gdt_entry gdt[GDT_ENTRIES];
struct gdt_ptr gp;

void gdt_setup_descriptor(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char granularity)
{
	gdt[num].base_low = (base & 0xFFFF);
	gdt[num].base_middle = (base >> 16) & 0xFF;
	gdt[num].base_high = (base >> 24) & 0xFF;
	gdt[num].limit_low = (limit & 0xFFFF);
	gdt[num].granularity = ((limit >> 16) & 0x0F);
	gdt[num].granularity |= (granularity & 0xF0);
	gdt[num].access = access;
}

void setup_gdt()
{
	gp.limit = (sizeof(struct gdt_entry) * GDT_ENTRIES) - 1;
	gp.base = (uint32_t)&gdt;

	gdt_setup_descriptor(0, 0, 0, 0, 0);
	gdt_setup_descriptor(1, 0, 0xFFFFF, 0x9A, 0xC0);
	gdt_setup_descriptor(2, 0, 0xFFFFF, 0x92, 0xC0);

	reload_gdt();
}
