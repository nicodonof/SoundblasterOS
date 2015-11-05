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

%macro pusha 0
    push rax
    push rbx
    push rcx
    push rdx
    push rdi
    push rsi
%endmacro

%macro popa 0
    pop rsi
    pop rdi
    pop rdx
    pop rcx
    pop rbx
    pop rax
%endmacro

timerHandler:
    
    pusha
    
    call keyboarddddd
    
    call _EOI

    popa
	iretq

keyboardHandler:
    pusha

    mov rax, 0
    in al,60h
    mov rdi, rax

    call write_key
    
    call _EOI
    
    popa
    iretq

syscallHandlerA:
    pusha
    call syscallHandler
    popa
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
