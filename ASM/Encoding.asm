use16
org 100h
    jmp START;
;------------------------------------------
buffer db 100 dup(?)
;------------------------------------------

START:
    mov ah, 0ah
    lea dx, [buffer]
    mov byte[buffer], 100
    int 21h
    inc dx
    mov bx, dx
    mov al, [bx]
    mov ah, 0
    inc dx
    add bx, ax
    mov byte[bx], '$'

    mov cx, ax
    mov ah, 1
    push cx
    mov bx, dx
    coding:
        mov cl, ah
        mov al, byte[bx]
        ror al, cl
        mov byte[bx], al

        inc ah
        cmp ah, 8
        jnz forward1
        mov ah, 1
        forward1:
        inc bx
        mov ah, cl
        loop coding

    mov bx, dx
    pop cx
    mov ah, 1
    encoding:
        mov cl, ah
        mov al, byte[bx]
        rol al, cl
        mov byte[bx], al

        inc ah
        cmp ah, 8
        jnz forward2
        mov ah, 1
        forward2:
        inc bx
        mov ah, cl
        loop encoding

    mov ah, 09h
    int 21h

exit:
    mov ax, 4C00h
    int 21h
