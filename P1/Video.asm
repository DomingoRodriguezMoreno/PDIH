pila segment stack 'stack'
	dw 100h dup (?)
pila ends

datos segment 'data'
	msg db 'Cambio de modo realizado, esperando ... $'
datos ends

codigo segment 'code'
	assume cs:codigo, ds:datos, ss:pila
	main PROC
		mov ax,datos
		mov ds,ax

		; poner modo de video 40x25
		mov al,0 ; modo de 40x25
		mov ah,0 ; funcion de poner modo de video
		int 10h

		; escribir una cadena
		mov dx,OFFSET msg
		mov ah,9
		int 21h

		; hacer una pausa esperando una tecla
		mov ah,08h
		int 21h

		; poner modo de video 80x25
		mov al,3 ; modo de 80x25
		mov ah,0 ; funcion de poner modo de video
		int 10h

        ; terminar y salir
        mov ax, 4C00h
		int 21h

	main ENDP
codigo ends

END main
