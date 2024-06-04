all: setup

setup:
	gcc -o main main.c
	echo "This is a secret content." > secret_file.txt
	chmod 400 secret_file.txt
	./main secret_file.txt
	su -c "./main secret_file.txt" regularuser
	chmod 4755 main
	useradd regularuser
	su -c "./main secret_file.txt" regularuser
	./main secret_file.txt

clean:
	rm -f main secret_file.txt
	userdel regularuser

.PHONY: all clean setup
