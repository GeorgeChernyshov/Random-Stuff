power:
    push %ecx; 
    mov $1, %ecx;
    test %edx, %edx;
    jnz loop;

end:
    mov %ecx, %eax;
    pop %ecx;
    ret;
    
loop:
    imul %eax, %ecx;
    dec %edx;
    test %edx, %edx;
    jnz loop;
    jmp end;
