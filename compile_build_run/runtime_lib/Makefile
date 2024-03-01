runtime_hello:
	gcc -c lib_runtime_hello.c -fPIC -o lib_runtime_hello.o
	gcc -shared lib_runtime_hello.o -o lib_runtime_hello.so
	gcc runtime_hello.c -o runtime_hello
