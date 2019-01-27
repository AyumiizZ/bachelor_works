	.file	"2.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Sorted string is %s\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB34:
	.cfi_startproc
	subq	$2088, %rsp
	.cfi_def_cfa_offset 2096
	movdqa	.LC1(%rip), %xmm0
	movq	%fs:40, %rax
	movq	%rax, 2072(%rsp)
	xorl	%eax, %eax
	movaps	%xmm0, 1024(%rsp)
	movabsq	$7960240367629526884, %rax
	movl	$1969582945, 1064(%rsp)
	movb	$0, 1070(%rsp)
	movdqa	.LC2(%rip), %xmm0
	movq	%rax, 1056(%rsp)
	movl	$26738, %eax
	movw	%ax, 1068(%rsp)
	movq	%rsp, %rax
	movaps	%xmm0, 1040(%rsp)
	leaq	1024(%rax), %rdx
	movq	%rax, %rcx
	.p2align 4,,10
	.p2align 3
.L2:
	addq	$4, %rcx
	movl	$0, -4(%rcx)
	cmpq	%rdx, %rcx
	jne	.L2
	leaq	1024(%rsp), %rdx
	movl	$97, %r8d
	movl	$99, %esi
	leaq	2(%rdx), %rdi
	movq	%rdi, %r9
	jmp	.L4
	.p2align 4,,10
	.p2align 3
.L15:
	movzbl	(%r9), %r10d
	movsbq	%r8b, %rsi
	addq	$1, %r9
	movl	%r10d, %r8d
.L4:
	addl	$1, (%rsp,%rsi,4)
	testb	%r8b, %r8b
	jne	.L15
	addq	$4, %rax
	.p2align 4,,10
	.p2align 3
.L5:
	movl	-4(%rax), %esi
	addl	%esi, (%rax)
	addq	$4, %rax
	cmpq	%rcx, %rax
	jne	.L5
	movl	$97, %r8d
	movl	$99, %ecx
	jmp	.L7
	.p2align 4,,10
	.p2align 3
.L16:
	movzbl	(%rdi), %eax
	movl	%r8d, %ecx
	addq	$1, %rdi
	movl	%eax, %r8d
.L7:
	movsbq	%cl, %rsi
	movl	(%rsp,%rsi,4), %eax
	subl	$1, %eax
	testb	%r8b, %r8b
	movslq	%eax, %r9
	movl	%eax, (%rsp,%rsi,4)
	movb	%cl, 1072(%rsp,%r9)
	jne	.L16
	leaq	1072(%rsp), %rsi
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L6:
	movzbl	(%rsi,%rax), %ecx
	movb	%cl, (%rdx,%rax)
	addq	$1, %rax
	cmpb	$0, (%rdx,%rax)
	jne	.L6
	leaq	.LC0(%rip), %rsi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk@PLT
	xorl	%eax, %eax
	movq	2072(%rsp), %rdi
	xorq	%fs:40, %rdi
	jne	.L17
	addq	$2088, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L17:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE34:
	.size	main, .-main
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC1:
	.quad	8241982499847430499
	.quad	7450159129608287336
	.align 16
.LC2:
	.quad	7009106699546686308
	.quad	8308105858017223795
	.ident	"GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
