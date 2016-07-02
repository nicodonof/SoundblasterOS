global loader
global forceScheduler
extern main
extern initializeKernelBinary
extern schedulerToKernel
extern schedulerToUser
extern processNext

%macro pusha 0
    push rax
    push rbx
    push rcx
    push rdx
    push rdi
    push rsi
    push rbp
%endmacro

%macro popa 0
    pop rbp
    pop rsi
    pop rdi
    pop rdx
    pop rcx
    pop rbx
    pop rax
%endmacro



loader:
	call initializeKernelBinary	; Set up the kernel binary, and get thet stack address
	mov rsp, rax				; Set up the stack with the returned address
	
	call main
	cli
hang:
	hlt							; halt machine should kernel return
	jmp hang

forceScheduler:
	;Mejorar y explicar	
	;Simulamos una interrpucion
	pop 		QWORD[ret_addr] 			;Direccion de retorno

	mov 		QWORD[ss_addr],	ss 		;Stack Segment
	push 		QWORD[ss_addr]

	push  		rsp
	pushf 									;Se pushean los flags
	mov 		QWORD[cs_addr], cs 		;Code Segment
	push 		QWORD[cs_addr]
	push 		QWORD[ret_addr] 			;Direccion de retorno

	;En este momento el stack contiene:
	;
	; > red_addr
	;	cs
	;	rflags
	;	rsp
	; 	ss

	pusha

	mov 		rdi,	 rsp
	call 		schedulerToKernel
	mov 		rsp, 	rax

	call 		processNext

	call  		schedulerToUser
	mov			rsp,	 rax

	popa
	iretq

section .bss

ret_addr:
		resq 1
cs_addr:
		resq 1
ss_addr:
		resq 1