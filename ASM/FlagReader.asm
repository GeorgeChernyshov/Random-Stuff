use16
org 100h
    jmp START;
;------------------------------------------
buffer db 100 dup(?)
;------------------------------------------

START:
    lahf
    mov cl, ah
    xor bl, bl
    shl cl, 1
    adc dl, 0
    shl cl, 1
    adc dl, 0
    shl cl, 6
    adc dl, 0
    cmp dl, 1
    jg inverse

exit:
    mov ax, 4C00h
    int 21h

inverse:
    cmc
    jmp exit
