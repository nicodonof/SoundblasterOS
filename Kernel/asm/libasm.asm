GLOBAL outb
GLOBAL inb

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