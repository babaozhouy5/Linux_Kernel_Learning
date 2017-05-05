funA:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	addl	$2, %eax
	popl	%ebp
	ret
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$2, -4(%ebp)
	pushl	-4(%ebp)
	call	funA
	addl	$4, %esp
	leave
	ret
