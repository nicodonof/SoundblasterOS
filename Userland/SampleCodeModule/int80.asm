GLOBAL syscaller

syscaller:
	push rax
	int 80h
	pop rax
	ret