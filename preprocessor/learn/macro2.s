    @ This is outputed using `gcc -S macro2.c -o macro2.s`
	.file	"macro2.c"      @ Tells us the file name
	.text
	.globl	main
	.type	main, @function
main:       @ Laeling the starting memory address of the main function
.LFB0:
	.cfi_startproc
	pushq	%rbp    @ Save the previous functions stacks base pointers
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp  @ Set up the stack frame
	.cfi_def_cfa_register 6
	movl	$50, -4(%rbp)   @ This is the code int x = X, it is moving the value 50 into the stack memory space allocated for x
	addl	$50, -4(%rbp)   @ This is adding 50 to it || can easily remove this and remove the addition arithmetic alltogether
	movl	$0, %eax        @ The hidden return statement, return 0 in main
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 16.1.1 20260728"
	.section	.note.GNU-stack,"",@progbits
