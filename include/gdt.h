/**
 * Global Descriptor Table structure and configuration
 */

#ifndef __GDT__
#define __GDT__

#include <stdint.h>
#include <stdbool.h>

struct gdt_entry
{
	unsigned short limit_low; //!< Lower bytes of address limit
	unsigned short base_low; //!< Lower bytes of base address
	unsigned char base_middle; //!< Middle bytes of base address
	unsigned char access; //!< Access flags
	unsigned char granularity; //!< Granularity (TODO: find out what this is supposed to do)
	unsigned char base_high; //!< Higher bytes of base address
} __attribute__((packed));

struct gdt_ptr
{
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));

void setup_gdt();
void gdt_setup_descriptor(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char granularity);
extern void reload_gdt();

#endif
