hello_world:
	gcc hello.c -o hello

sys_hello:
		gcc sys_hello.c -o sys_hello

syscall_mywrite:
	gcc syscall_mywrite.c -o syscall_mywrite

nosys_hello:
	gcc nosys_hello.c -o nosys_hello

nosys_hello1:
	gcc nosys_hello1.c -o nosys_hello1

asm_hello:
	as hello_world.S -o asm_hello.o
	gcc -no-pie -nostartfiles asm_hello.o -o asm_hello

