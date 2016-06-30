GLOBAL outb
GLOBAL inb
GLOBAL write_cr3
GLOBAL get_cr3
GLOBAL set_paging

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

get_cr3:
	push rbp
	mov rbp,rsp
	mov rax, cr3
	and rax, 0xFFFFFFFFF000
	mov rsp, rbp
	pop rbp
	ret
	
write_cr3:
	or rdi, 0x8
	mov cr3, rdi
	ret

write_cr4_backup:
	mov cr3, rdi
	ret

set_paging:
	mov rax, cr0
	or al, 0x01			; Set protected mode bit
	mov cr0, rax