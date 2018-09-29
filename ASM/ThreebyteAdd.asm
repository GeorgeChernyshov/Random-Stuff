use16
org 100h
    mov ax, word[x]
    add ax, word[y]
    mov word[z], ax
    
    mov al, byte[x+2]
    adc al, byte[y+2]
    mov byte[z], al
    
    mov ax, 4C00h
    int 21h
