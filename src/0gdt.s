; GDT reload code

extern gp
global reload_gdt
reload_gdt:
    lgdt [gp]
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:reload_gdt_ret
reload_gdt_ret:
    ret
