[org 0x100]

jmp start

oldkb: dd 0													; variable to store original kbisr
terminate: db 0												; flag to terminate the program

ticks_to_second: db 0										; counts the no if ticks to a second
seconds: dw 0												; no of seconds elapsed (total game time)
remainder: db 0												; variable used in divide subroutine

left_flag: db 0												; check to see if asterisk is to move to the left
right_flag: db 1											; check to see if the asterisk is to move to the right
down_flag: db 0												; check to see if asterisk is to move down
up_flag: db 0												; check to see if asterisk is to move up

x: dw 0														; stores x coordinate of the asterisk
y: dw 1														; stores y coordinate of the asterisk
															
score: dw 0													; stores the score of the player

time_string: db "time (seconds):"							; strings to print text
score_string: db "Game Over. Your Score:"					; strings to print text
score_string_1: db "Your Score:"							; strings to print text

kbisr:														; keyboard interrupt
	push ax
	in al, 0x60
															; compares scan code to set direction
	cmp al, 0x48
	jz set_up
	cmp al, 0x4B
	jz set_left
	cmp al, 0x4D
	jz set_right
	cmp al, 0x50
	jz set_down

	jne no_match

	set_up:													; sets direction flag
		mov byte [cs: left_flag], 0
		mov byte [cs: right_flag], 0
		mov byte [cs: down_flag], 0
		mov byte [cs: up_flag], 1
		jmp exit

	set_down:
		mov byte [cs: left_flag], 0
		mov byte [cs: right_flag], 0
		mov byte [cs: down_flag], 1
		mov byte [cs: up_flag], 0
		jmp exit

	set_right:
		mov byte [cs: left_flag], 0
		mov byte [cs: right_flag], 1
		mov byte [cs: down_flag], 0
		mov byte [cs: up_flag], 0
		jmp exit

	set_left:
		mov byte [cs: left_flag], 1
		mov byte [cs: right_flag], 0
		mov byte [cs: down_flag], 0
		mov byte [cs: up_flag], 0
		jmp exit

no_match:												  ; paths to return from interrupt and signal end of interrupt signal
	pop ax
	jmp far [cs:oldkb]
exit:
	mov al, 0x20
	out 0x20, al
	pop ax
	iret

timer:													  ; timer interrupt
	
	push ax
	
		cmp byte [cs:terminate], 1						  ; checks if timer has enough ticks for a second
		je exit_timer
		cmp byte [cs:ticks_to_second], 18
		jne increment
		inc word [cs:seconds]
		mov byte [cs:ticks_to_second], 0

		call move_asterisk								  ; moves asterisk if it has enought ticks
		jmp end_of_timer

		increment:
			inc byte [cs:ticks_to_second]

		end_of_timer:									  ; prints updated time and score and then exists
			push word 158
			push word [cs: seconds]
			call print_num

			push word 30
			push word [cs:score]
			call print_num

		exit_timer:	
			mov al, 0x20								  ; signals end of interrupt and returns
			out 0x20, al

	pop ax
iret
		

print_num:												  ; subroutine to print number at given index of screen
	push bp
	mov bp, sp
	
		push es
		push di
		push ax
		push dx
		
			mov ax, 0xb800								  ; sets es to video memory
			mov es, ax
		
			xor dx, dx									  
			mov dh, 0x07								  ; sets attribute as white on black
		
			mov ax, [bp+4]								  ; moves number to ax
			mov di, [bp+6]								  ; moves location to di
		
			cmp ax, 0									  ; checks is number is zero
			jne print_num_loop
			mov word [es:di], 0x0730
			jmp end_print_num
		
			print_num_loop:
				call divide								  ; divides number by 10 to get least significant decimal
				mov dl, [remainder]						  ; moves the least significant decimal to dl
				add dl, 0x30							  ; converts number to its ascii form
				mov [es:di], dx
				sub di, 2
				cmp ax, 0
			jne print_num_loop
		
		
		end_print_num:									  ; restores values to registers and returns
		pop dx
		pop ax
		pop di
		pop es
	
	pop bp
ret 4
														  ; subroutine to divide a number by 10
divide:
push dx
push bx

	mov bx, 10											  ; moves divisor to bx
	;cmp ax, 0xff										

	byte_divide:										  ; divides number in ax by bl
		div bl
		mov [remainder], ah								  ; moves remainder in variable
		mov ah,0										  ; clears ah

end_divide:												  ; restores register values and returns
pop bx
pop dx
ret

print_screen:
	push es
	push ax
	push di
	push cx

		mov ax, 0xb800
		mov es, ax
		mov di, 0

		mov cx, 80
		mov ax, 0x0720
		rep stosw

		mov word [es:di], 0x072A
		add di, 2

		mov cx, 29
		mov ax, 0x2020
		rep stosw

		mov cx, 20
		mov ax, 0x4020
		rep stosw

		mov cx, 620 
		mov ax, 0x2020
		rep stosw

		mov cx, 20
		mov ax, 0x4020
		rep stosw

		mov cx, 540
		mov ax, 0x2020
		rep stosw

		mov cx, 20
		mov ax, 0x4020
		rep stosw

		mov cx, 620
		mov ax, 0x2020
		rep stosw

		mov cx, 20
		mov ax, 0x4020
		rep stosw

		mov cx, 30
		mov ax, 0x2020
		rep stosw

		mov ax, 0x4020
		mov cx, 8
		mov di, 1440
		mov si, di
		add si, 158

		vertical:
			mov [es:di], ax
			mov [es:si], ax
			add di, 160
			add si, 160
			loop vertical

	pop cx
	pop di
	pop ax
	pop es

ret

move_asterisk:

	call print_space
	
	cmp byte [cs: left_flag], 1
	je move_left
	cmp byte [cs: right_flag], 1
	je move_right
	cmp byte [cs: down_flag], 1
	je move_down
	cmp byte [cs: up_flag], 1
	je move_up

	move_left:
		cmp word [cs:x], 0
		jne simple_left
		mov word [cs:x], 79
		jmp end_of_move
		simple_left:
		dec word [cs:x]
		jmp end_of_move

	move_right:
		cmp word [cs:x], 79
		jne simple_right
		mov word [cs:x], 0
		jmp end_of_move
		simple_right:
		inc word [cs:x]
		jmp end_of_move

	move_down:
		cmp word [cs:y], 24
		jne simple_down
		mov word [cs:y], 1
		jmp end_of_move
		simple_down:
		inc word [cs:y]
		jmp end_of_move

	move_up:
		cmp word [cs:y], 1
		jne simple_up
		mov word [cs:y], 24
		jmp end_of_move
		simple_up:
		dec word [cs:y]
		jmp end_of_move

end_of_move:
call print_asterisk
ret

print_space:
	push es
	push ax
	push di
	push cx

		mov ax, 0xb800
		mov es, ax
		mov di, 0

		mov cx, [cs:x]
		x_increment_space:
			add di, 2
			loop x_increment_space

		mov cx, [cs:y]
		y_increment_space:
			add di, 160
			loop y_increment_space

		mov word [es:di], 0x0720

	pop cx
	pop di
	pop ax
	pop es
ret

print_asterisk:
	push es
	push ax
	push di
	push cx


		mov ax, 0xb800
		mov es, ax
		mov di, 0

		mov cx, [cs:x]
		x_increment:
			add di, 2
			loop x_increment

		mov cx, [cs:y]
		y_increment:
			add di, 160
			loop y_increment

		cmp word [es:di], 0x4020
		jne skip1
		mov byte [cs:terminate], 1		
		
		skip1:
		cmp word [es:di], 0x2020
		jne skip
		add word [cs:score], 1

		skip:
		mov word [es:di], 0x072A

	pop cx
	pop di
	pop ax
	pop es
ret

print_string:
	push bp
	mov bp, sp

	push cx
	push bx

	push ax
	push es
	push di

		mov bx, [bp+6]

		mov ax, 0xb800
		mov es, ax
		mov di, [bp+8]

		mov cx, [bp+4]

		mov ah, 0x07
		print_loop:
			mov al, [bx]
			stosw
			inc bx
			loop print_loop

	pop di
	pop es
	pop ax

	pop bx
	pop cx

	pop bp
ret 6

clrscr:

	push cx				;pushes to save original values
	push ax				;pushes to save original values
	push es				;pushes to save original values
	push di				;pushes to save original values
	
	mov ax, 0xB800		;initializes es and di
	mov es, ax			;initializes es and di
	mov di, 0			;initializes es and di
	
	mov ax, 0x0720		; code to clear screen
	mov cx, 2000		; code to clear screen
	cld					; code to clear screen
	rep stosw			; code to clear screen
	
	pop di				; pops values to restore original
	pop es				; pops values to restore original
	pop ax				; pops values to restore original
	pop cx				; pops values to restore original

ret						; returns from subroutine


start:
	
	xor ax, ax
	mov es, ax

	mov word [es: 8*4], timer
	mov [es: 8*4+2], cs

	cli
	mov ax, [es: 9*4]
	mov [oldkb], ax
	mov ax, [es: 9*4+2]
	mov [oldkb+2], ax

	mov word [es: 9*4], kbisr
	mov [es: 9*4+2],cs
	sti

	call print_screen
	push word 120
	push word time_string
	push word 15
	call print_string
	push word 0
	push word score_string_1
	push word 11
	call print_string

	l1:
	cmp byte [terminate], 1
	jne l1

	cli
	mov ax, [oldkb]
	mov word [es: 9*4], ax
	mov ax, [oldkb + 2]
	mov [es: 9*4+2],ax
	sti

	call clrscr

	push word 1972
	push word score_string
	push word 22
	call print_string

	push word 2024
	push word [score]
	call print_num

mov ax, 0x4c00
int 21h
