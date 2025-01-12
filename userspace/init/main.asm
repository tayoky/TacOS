[BITS 64]
global _start

section .text
_start:
    mov rax, 2     ; open(
    mov rdi, fname ;    "/dev/tty0",
    mov rsi, 0     ;    0,
    mov rdx, 9     ;    9
    int 0x80       ; );
    mov r11, rax
    mov rax, 1           ; write(
    mov rdi, r11         ;    f,
    mov rsi, msg         ;    msg,
    lea rdx, [end - msg] ;    strlen(msg)
    int 0x80             ; );
    mov rax, 4 ; exit(
    mov rdi, 0 ;    0
    int 0x80   ; );

section .rodata
fname: db "/dev/tty0", 0
msg:   db "Hello world from userspace!", 0
end:
