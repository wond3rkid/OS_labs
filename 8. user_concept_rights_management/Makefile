all: setup

setup:
	touch secret_file.txt
	chmod 400 secret_file.txt
	echo "This is a secret content." > secret_file.txt
	gcc -o main main.c
	sudo chown root:root main
	sudo chmod 4755 main

clean:
	rm -f main secret_file.txt

.PHONY: all clean setup
