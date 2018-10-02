use16
org 100h
    jmp START;
;------------------------------------------
a db ?
b db ?
less db 'a < b$'
more db 'a > b$'
equal db 'a = b$'
buffer db 10 dup(?)
;------------------------------------------
readNumber:
    push dx
    push cx
    push bx

    mov ah, 0ah
    lea dx, [buffer]
    mov byte[buffer], 5
    int 21h

    mov cl, byte[buffer+1]
    mov ch, 0
    mov ax, 0
    mov bx, buffer
    add bx, 2
    mov dx, 1

    convertSymbol:
        imul ax, 10
        mov dl, [bx]
        sub dl, '0'
        add ax, dx
        imul bx, dx
        loop convertSymbol

    pop bx
    pop cx
    pop dx
ret

START:
    call readNumber
    push ax
    call readNumber
    pop bx

    cmp ax, bx
    je onEqual
    jl onGreater
    mov dx, less
    mov ah, 09h
    int 21h

exit:
    mov ax, 4C00h
    int 21h

onEqual:
    mov dx, equal
    mov ah, 09h
    int 21h
    jmp exit

onGreater:
    mov dx, more
    mov ah, 09h
    int 21h
    jmp exit
