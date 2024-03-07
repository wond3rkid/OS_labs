hello_world:
	gcc hello.c -o hello

sys_hello:
		gcc sys_hello.c -o sys_hello

syscall_mywrite:
	gcc syscall_mywrite.c -o syscall_mywrite

asm_hello:
	as hello_world.S -o asm_hello.o
	gcc -no-pie -nostartfiles asm_hello.o -o asm_hello

