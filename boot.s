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

//.section .gdt
//gdt_table:
//.byte	0xFF			;limit 0-7
//.byte	0xFF			;limit 8-15
//.byte				;base 0-7
//.byte				;base 8-15
//.byte				;base 16-23
//.byte	0b01111001			;access byte
//.byte	0xF0			;limit 16-19 + flags
//.byte				;base 24-31
	
//gdt_des
	
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

.global isr0
.global isr1
.global isr2
.global isr3
.global isr4
.global isr5
.global isr6
.global isr7
.global isr8
.global isr9
.global isr10
.global isr11
.global isr12
.global isr13
.global isr14
.global isr15
.global isr16
.global isr17
.global isr18
.global isr19
.global isr20
.global isr21
.global isr22
.global isr23
.global isr24
.global isr25
.global isr26
.global isr27
.global isr28
.global isr29
.global isr30
.global isr31


isr0:
	cli
	push	$0x00
	push	$0x00
	jmp	$0x08, $isr_common_stub

isr1:
	cli
	push	$0x00
	push	$0x01
	jmp	$0x08, $isr_common_stub

isr2:
	cli
	push	$0x00
	push	$0x02
	jmp	$0x08, $isr_common_stub

isr3:
	cli
	push	$0x00
	push	$0x03
	jmp	$0x08, $isr_common_stub

isr4:
	cli
	push	$0x00
	push	$0x04
	jmp	$0x08, $isr_common_stub

isr5:
	cli
	push	$0x00
	push	$0x05
	jmp	$0x08, $isr_common_stub

isr6:
	cli
	push	$0x00
	push	$0x06
	jmp	$0x08, $isr_common_stub

isr7:
	cli
	push	$0x00
	push	$0x07
	jmp	$0x08, $isr_common_stub

isr8:
	cli
	push	$0x08
	jmp	$0x08, $isr_common_stub

isr9:
	cli
	push	$0x00
	push	$0x09
	jmp	$0x08, $isr_common_stub
	
isr10:
	cli
	push	$0x0A
	jmp	$0x08, $isr_common_stub

isr11:
	cli
	push	$0x0B
	jmp	$0x08, $isr_common_stub

isr12:
	cli
	push	$0x0C
	jmp	$0x08, $isr_common_stub

isr13:
	cli
	push	$0x0D
	jmp	$0x08, $isr_common_stub

isr14:
	cli
	push	$0x0E
	jmp	$0x08, $isr_common_stub

isr15:
	cli
	push	$0x00
	push	$0x0F
	jmp	$0x08, $isr_common_stub

isr16:
	cli
	push	$0x00
	push	$0x10
	jmp	$0x08, $isr_common_stub

isr17:
	cli
	push	$0x00
	push	$0x11
	jmp	$0x08, $isr_common_stub

isr18:
	cli
	push	$0x00
	push	$0x12
	jmp	$0x08, $isr_common_stub

isr19:
	cli
	push	$0x00
	push	$0x13
	jmp	$0x08, $isr_common_stub

isr20:
	cli
	push	$0x00
	push	$0x14
	jmp	$0x08, $isr_common_stub

isr21:
	cli
	push	$0x00
	push	$0x15
	jmp	$0x08, $isr_common_stub

isr22:
	cli
	push	$0x00
	push	$0x16
	jmp	$0x08, $isr_common_stub

isr23:
	cli
	push	$0x00
	push	$0x17
	jmp	$0x08, $isr_common_stub

isr24:
	cli
	push	$0x00
	push	$0x18
	jmp	$0x08, $isr_common_stub

isr25:
	cli
	push	$0x00
	push	$0x19
	jmp	$0x08, $isr_common_stub

isr26:
	cli
	push	$0x00
	push	$0x1A
	jmp	$0x08, $isr_common_stub

isr27:
	cli
	push	$0x00
	push	$0x1B
	jmp	$0x08, $isr_common_stub

isr28:
	cli
	push	$0x00
	push	$0x1C
	jmp	$0x08, $isr_common_stub

isr29:
	cli
	push	$0x00
	push	$0x1D
	jmp	$0x08, $isr_common_stub

isr30:
	cli
	push	$0x00
	push	$0x1E
	jmp	$0x08, $isr_common_stub

isr31:
	cli
	push	$0x00
	push	$0x1F
	jmp	$0x08, $isr_common_stub
	
.extern fault_handler

isr_common_stub:
	pusha
	push	%ds
	push	%es
	push	%fs
	push	%gs
	movw	$0x10, %ax
	movw	%ax, %ds
	movw	%ax, %es
	movw	%ax, %fs
	movw	%ax, %gs
	movl	%esp, %eax
	pushl	%eax
	movl	$fault_handler, %eax
	calll	%eax
	popl	%eax
	pop	%gs
	pop	%fs
	pop	%es
	pop	%ds
	popa
	addl	$8, %esp
	iret

.section .bootstrap_stack
stack_bottom:
.skip 16384
stack_top:
	
