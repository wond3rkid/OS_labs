.data

msg:
	.ascii "Hello world\n"
	len = . - msg
.text
	.global _start

_start:
	movq $4, %rax
	movq $1, %rbx
	movq $msg, %rcx
	movq $len, %rdx

	int $0x80
	mov $1, %eax    
	xor %ebx, %ebx 
	int $0x80      
