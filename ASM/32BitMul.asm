use16               ;Генерировать 16-битный код
org 100h            ;Программа начинается с адреса 100h
 
    mov ax,word[a]
    mul word[b]
    mov di,ax
    mov si,dx
    sub cx,cx
    sub bx,bx
 
    mov ax,word[a+2]
    mul word[b]
    add si,ax
    adc cx,dx
 
    mov ax,word[a]
    mul word[b+2]
    add si,ax
    adc cx,dx
    adc bx,0
 
    mov ax,word[a+2]
    mul word[b+2]
    add cx,ax
    adc bx,dx
 
    mov word[c],di
    mov word[c+2],si
    mov word[c+4],cx
    mov word[c+6],bx
 
    mov ax,4C00h    ;
    int 21h         ;/ Завершение программы
;-------------------------------------------------------
align 4
a   dd $FFFFFFFF
b   dd $FFFFFFFF
c   dq ?
