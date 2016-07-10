global loader
global forceScheduler
extern main
extern initializeKernelBinary
extern schedulerToKernel
extern schedulerToUser
extern processNext
extern sPrintf
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



loader:
	call initializeKernelBinary	; Set up the kernel binary, and get thet stack address
	mov rsp, rax				; Set up the stack with the returned address
	
	call main
	cli

hang:
	hlt							; halt machine should kernel return
	jmp hang

forceScheduler:
	;Push de los registros que dps va a levantar el iretq
	
	pop 		QWORD[ret_addr] 		;Direccion de retorno

	mov 		QWORD[ss_addr],	ss 		;Stack Segment
	push 		QWORD[ss_addr]

	push  		rsp

	pushf 								;Se pushean los flags
	mov 		QWORD[cs_addr], cs 		;Code Segment
	push 		QWORD[cs_addr]
	push 		QWORD[ret_addr] 		;Direccion de retorno

	;En este momento el stack contiene:
	;
	; > ret_addr
	;	cs
	;	rflags
	;	rsp
	; 	ss

	pusha

	mov 		rdi, rsp
	call 		schedulerToKernel
	mov 		rsp, rax

	call 		processNext

	call  		schedulerToUser
	mov			rsp, rax

	popa

	iretq


section .bss

ret_addr:
		resq 1
cs_addr:
		resq 1
ss_addr:
		resq 1

section .data
	string db "rsp: %x",10,0
	ripppp db "rip: %x",10,0
	halt db "halt"
	start db "Start fs:",10,0
	end db "End fs.",10,0
