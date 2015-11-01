GLOBAL timerHandler
GLOBAL keyboardHandler
GLOBAL syscallHandlerA
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL _sti
GLOBAL _EOI
GLOBAL _iretq


extern write_key
extern keyboarddddd
extern syscallHandler

timerHandler:
    
    

	call keyboarddddd
    
    call _EOI

	iretq

keyboardHandler:
    
    
    
    mov rax, 0
    in al,60h
    
    mov rdi, rax
    call write_key
    call _EOI
    iretq

syscallHandlerA:

    call syscallHandler
    
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

_iretq:
    iretq
