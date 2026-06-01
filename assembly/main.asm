; main.asm
bits 64
global main
extern add
extern printf
extern exit

section .rodata         ; readonly data
    fmt db "Result: %d", 10, 0      ; format string into "Result: %d\n"

section .text
main:
    sub rsp, 8
    ; Setup arguments for add (15, 27)
    mov edi, 15                 ; first argument is in rdi, and edi is lower 32-bit of rdi
    mov esi, 27                 ; second argument is in rsi

    ; call the c function
    call add                    ; hardware pushes RIP to stack, jumps to add

    ; handle return value in rax (but now because we only used lower 32-bit eax)
    mov rsi, rax                ; move return value into 2nd argument
    mov rdi, fmt                ; move address of the format string into the 1st argument
    mov al, 0                   ; printf is variadic; 
    call printf

    ; exit cleanly via libc exit(0)
    mov edi, 0
    call exit
