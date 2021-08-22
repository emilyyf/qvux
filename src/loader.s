MBALIGN  equ 1 << 0
MEMINFO  equ 1 << 0
FLAGS    equ MBALIGN | MEMINFO
MAGIC    equ 0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

section .text
global _start:function (_start.end - _start)
_start:
	mov esp, stack_top
	extern kmain
	call kmain

	cli
.hang:
	hlt
	jmp .hang
.end:

section .bss
	align 16
stack_bottom:
	resb 1024 * 16
stack_top: