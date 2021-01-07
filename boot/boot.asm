[bits 16]
[org 0x7c00]

boot:
    mov [DISK], dl

    mov ax, 0x3
    int 0x10

    ; setup stack
    mov bp, 0x9000
    mov sp, bp

    ; load disk sectors
    mov bx, KERNEL_OFFSET
    mov dh, NUM_SECTORS
    mov dl, [DISK]
    call disk_load

    cli

    ; load gdt
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    jmp CODE_SEG:init_kernel

    jmp $


gdt_start:
    dq 0x0

gdt_code:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10011010b
    db 11001111b
    db 0x0

gdt_data:
    dw 0xffff
    dw 0x0 
    db 0x0  
    db 10010010b
    db 11001111b
    db 0x0

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

data:
    DISK db 0
    KERNEL_OFFSET equ 0x1000
    NUM_SECTORS equ 16

disk_load:
    pusha
    push dx

    mov ah, 0x02
    mov al, dh
    mov cl, 0x02
    mov ch, 0x00
    mov dh, 0x00

    int 0x13
    pop dx

    popa
    ret

[bits 32]
init_kernel:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; initialize stack
    mov ebp, 0x90000
    mov esp, ebp

    ; jump to kernel-entry.asm
    call KERNEL_OFFSET

    jmp $

times 510 - ($-$$) db 0
dw 0xaa55