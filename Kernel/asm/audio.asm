GLOBAL sounder
GLOBAL stop_sounder


sounder:
        push rax	
	mov     al, 182 	        ; Prepare the speaker for the
        out     43h, al         ;  note.
        mov     ax, 4560        ; Frequency number (in decimal)
                                ;  for middle C.
        out     42h, al         ; Output low byte.
        mov     al, ah          ; Output high byte.
        out     42h, al 
        in      al, 61h         ; Turn on note (get value from
                                ;  port 61h).
        or      al, 3           ; Set bits 1 and 0.
        out     61h, al         ; Send new value.
        pop rax        
        ret

stop_sounder:
        push rax

        in      al, 61h         ; Turn off note (get value from
                                ;  port 61h).
        and     al, 11111100b   ; Reset bits 1 and 0.
        out     61h, al       
        pop rax 
        ret