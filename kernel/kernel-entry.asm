[bits 32]
[extern kmain]

; kernel entry
kernel_entry:
    call kmain ; call kernel main function
    
    jmp $