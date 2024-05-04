static_hello:
	gcc -c lib_static_hello.c
	ar rs lib_static_hello.a lib_static_hello.o
	gcc -I . -c static_hello.c
	gcc static_hello.c -o static_hello -L. -l_static_hello
