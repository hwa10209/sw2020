Myshell :	main.o	pwd.o	ls.o	mkdir.o	
	gcc	 -o	Myshell	main.o	pwd.o	ls.o	mkdir.o

main.o	:	main.c	instructions.h
	gcc	-c	-o	main.o	main.c
pwd.o	:	pwd.c	instructions.h
	gcc	-c	-o	pwd.o	pwd.c
ls.o	:	ls.c	instructions.h
	gcc -c	-o	ls.o	ls.c
mkdir.o	:	mkdir.c	instructions.h
	gcc -c -o	mkdir.o	mkdir.c
clean	:
	rm *.o	Example
