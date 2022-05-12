Multi : multi_mat.o
	gcc -o Multi	multi_mat.o	-lpthread

multi_mat.o :	multi_mat.c
	gcc -c	-o	multi_mat.o	multi_mat.c

Single	:	single_mat.o
	gcc	-o	Single	single_mat.o	-lpthread

single_mat.o	:	single_mat.c
	gcc	-c	-o	single_mat.o	single_mat.c

clean	:
	rm *.o	Multi	Single
