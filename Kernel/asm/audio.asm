GLOBAL sounder

sounder:
	
	push rax
	mov al, 0xB6
	out 43h, al
	mov al, 54
	out 42h, al
	mov al, 124
	out 42h, al

	mov rax, 0
	in al, 61h
	or al, 3
	out 61h, al                         
	pop rax

	ret