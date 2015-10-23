GLOBAL keyboard
GLOBAL keyboard2
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL _sti
GLOBAL _EOI

extern vPrintChar
extern keyboardddd
extern keyboarddddd

keyboard:
    
    call _EOI

	call keyboarddddd
    
    

	iretq

keyboard2:
    
    mov rdi, 40
    call vPrintChar
    call _EOI
    
    call keyboardddd
    
    iretq

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    ret

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    ret

_sti:
	sti
	ret

_EOI:
    mov rax, 0
    mov al, 0x20
    out 0x20, al
    ret

