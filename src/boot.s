.set ALIGN,	1<<0
.set MEMINFO,	1<<1
.set FLAGS,	ALIGN | MEMINFO
.set MAGIC,	0x1BADB002
.set CHECKSUM,	-(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .text
.global _start
.type _start, @function
_start:
	sti
	movl $stack_top, %esp
	call kernel_main
	cli
	hlt
.Lhang:
	jmp .Lhang
.size _start, . - _start
	
.global gdt_flush
gdt_flush:	
	movl	4(%esp), %eax
	lgdt	(%eax)
	movw	$0x10, %ax
	movw	%ax, %ds
	movw	%ax, %es
	movw	%ax, %fs
	movw	%ax, %gs
	movw	%ax, %ss
	jmp	$0x08, $.flush
.flush:	
	ret

.global idt_load
idt_load:
	movl 4(%esp), %eax
	lidt (%eax)
	ret
	
.section .bootstrap_stack
stack_bottom:
.skip 16384
stack_top:
