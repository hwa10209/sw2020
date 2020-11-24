Bank : bank.o
	gcc -o Bank	bank.o	-lpthread

bank.o :	bank.c
	gcc -c	-o	bank.o	bank.c

Bank2	:	bank2.o
	gcc	-o	Bank2	bank2.o	-lpthread

bank2.o	:	bank2.c
	gcc	-c	-o	bank2.o	bank2.c

clean	:
	rm *.o	Bank	Bank2
