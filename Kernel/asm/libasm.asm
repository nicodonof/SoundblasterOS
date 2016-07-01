GLOBAL outb
GLOBAL inb
GLOBAL write_cr3
GLOBAL get_cr3
GLOBAL get_cr4
GLOBAL get_cr0
GLOBAL set_paging
extern sPrintf

outb:					;outb(value, port)
	mov rdx, rsi
	mov rax, rdi
	out dx, al
	ret

inb:
	mov rax, 0			;inb(value)
	mov rdx, rdi
	in al, dx
	mov rax, rdi
	ret

get_cr0:
	push rbp
	mov rbp,rsp
	mov rax, cr0
	;and rax, 0xFFFFFFFFF000
	mov rsp, rbp
	pop rbp
	ret

get_cr3:
	push rbp
	mov rbp,rsp
	mov rax, cr3
	;and rax, 0xFFFFFFFFF000
	mov rsp, rbp
	pop rbp
	ret

get_cr4:
	push rbp
	mov rbp,rsp
	mov rax, cr4
	;and rax, 0xFFFFFFFFF000
	mov rsp, rbp
	pop rbp
	ret
	
write_cr3:
	push rbp
	mov rbp, rsp
	cli
	
	or rdi, 8

	mov cr3, rdi

	sti
	mov rsp, rbp
	pop rbp
	ret

write_cr4_backup:
	mov cr3, rdi
	ret

set_paging:
	push rbp
	mov rbp, rsp

	mov rax, cr0
	
	
	mov rax, 0x0000000080000013


	mov cr0, rax

	mov rsp, rbp
	pop rbp
	ret

section .data
	string db "i: %x",10,0
	cr db "cr0: %x",10,0
