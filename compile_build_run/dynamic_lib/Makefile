dynamic_hello:
	gcc -Wall -fPIC -c lib_dynamic_hello.c
	gcc -shared -o lib_dynamic_hello.so lib_dynamic_hello.o
	sudo cp lib_dynamic_hello.so /lib
	sudo ldconfig
	gcc -c dynamic_hello.c
	gcc -o dynamic_hello dynamic_hello.o lib_dynamic_hello.so

