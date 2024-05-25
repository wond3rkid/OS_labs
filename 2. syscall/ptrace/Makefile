all: setup

setup:
	gcc -o hello hello.c
	gcc -o main main.c
	./main hello

clean:
	rm -f main hello

.PHONY: all clean setup
	gcc main.c -o main
	gcc hello.c -o hello
