test:
	gcc links_handler.c main.c file_dir_handler.c
	./a.out a ./tmp #create dir
	./a.out d ./tmp/iloveos #touch file1
	./a.out d ./tmp/hi_guys #touch file2
	@echo "its really interesting subject\n" > ./tmp/iloveos
	./a.out e ./tmp/iloveos #get text from file
	./a.out b ./tmp #ls tmp
	./a.out m ./tmp/iloveos #rights and links
	./a.out f ./tmp/hi_guys
	./a.out g ./tmp/iloveos
	ln -s ./tmp/iloveos ./tmp/symoslink
	./a.out i ./tmp/symoslink
	./a.out h ./tmp/symoslink
	./a.out j ./tmp/symoslink
	./a.out l ./tmp/iloveos
	./a.out c ./tmp