section .text
	global _start

section .data
msg db "x86 assembly test", 0xa
len equ $ - msg

section .text
_start:
	mov edx, len
	mov ecx, msg
	mov ebx, 1
	mov eax, 4
	int 0x80
	mov ebx, 69
	mov eax, 1
	int 0x80
