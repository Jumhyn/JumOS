.section .text

.macro ISR_NOERR num
.global isr\num
isr\num:
	cli
	push $0
	push $\num
	jmp isr_common_stub
.endm

.macro ISR_ERR num
.global isr\num
isr\num:
	cli
	push $\num
	jmp isr_common_stub
.endm

.macro IRQ num, int
.global irq\num
irq\num:
	cli
	push $0
	push $\int
	jmp irq_common_stub
.endm
	
	ISR_NOERR 0
	ISR_NOERR 1
	ISR_NOERR 2
	ISR_NOERR 3
	ISR_NOERR 4
	ISR_NOERR 5
	ISR_NOERR 6
	ISR_NOERR 7
	ISR_ERR 8
	ISR_NOERR 9
	ISR_ERR 10
	ISR_ERR 11
	ISR_ERR 12
	ISR_ERR 13
	ISR_ERR 14
	ISR_NOERR 15
	ISR_NOERR 16
	ISR_NOERR 17
	ISR_NOERR 18
	ISR_NOERR 19
	ISR_NOERR 20
	ISR_NOERR 21
	ISR_NOERR 22
	ISR_NOERR 23
	ISR_NOERR 24
	ISR_NOERR 25
	ISR_NOERR 26
	ISR_NOERR 27
	ISR_NOERR 28
	ISR_NOERR 29
	ISR_NOERR 30
	ISR_NOERR 31

	IRQ 0, 32
	IRQ 1, 33
	IRQ 2, 34
	IRQ 3, 35
	IRQ 4, 36
	IRQ 5, 37
	IRQ 6, 38
	IRQ 7, 39
	IRQ 8, 40
	IRQ 9, 41
	IRQ 10, 42
	IRQ 11, 43
	IRQ 12, 44
	IRQ 13, 45
	IRQ 14, 46
	IRQ 15, 47
	
.extern isr_handler
.extern irq_handler
	
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
	movl	$isr_handler, %eax
	calll	*%eax
	popl	%eax
	pop	%gs
	pop	%fs
	pop	%es
	pop	%ds
	popa
	addl	$8, %esp
	sti
	iret

irq_common_stub:
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
	movl 	$irq_handler, %eax
	call	*%eax
	popl	%eax
	pop	%gs
	pop	%fs
	pop	%es
	pop	%ds
	popa
	addl	$8, %esp
	sti
	iret
