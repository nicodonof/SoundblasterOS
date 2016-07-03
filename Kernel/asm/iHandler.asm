GLOBAL timerHandler
GLOBAL keyboardHandler
GLOBAL syscallHandlerA
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL _sti
GLOBAL _cli
GLOBAL _EOI
GLOBAL _iretq


extern write_key
extern keyboarddddd
extern syscallHandler
extern schedulerToKernel
extern schedulerToUser
extern processNext
extern getQuantum
extern decQuantum

%macro pusha 0
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rdi
    push rsi
    push r8 
    push r9 
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
    push fs 
    push gs 
%endmacro

%macro popa 0
    pop  gs
    pop  fs
    pop  r15
    pop  r14
    pop  r13
    pop  r12
    pop  r11
    pop  r10
    pop  r9 
    pop  r8 
    pop  rsi
    pop  rdi
    pop  rbp
    pop  rdx
    pop  rcx
    pop  rbx
    pop  rax
%endmacro

timerHandler:
    pusha
    call    keyboarddddd
    
    call    getQuantum
    cmp     rax, 0
    jne     _leave_current

    mov     rdi, rsp
    call    schedulerToKernel
    mov     rsp, rax

    call    processNext

    call    schedulerToUser
    mov     rsp, rax
    call    _EOI

    popa
	iretq

_leave_current:
    call decQuantum
    call    _EOI
    popa
    iretq

keyboardHandler:
    pusha

    mov rax, 0
    in al,60h
    mov rdi, rax
    
    call _EOI
    call write_key
       
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
_cli:
    cli
    ret

_EOI:
    
    mov rax, 0
    mov al, 0x20
    out 0x20, al
    
    ret
