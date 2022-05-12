#include "instructions.h"

int ls(int a){
	int	pid, status;
	char* argv[]= {"ls"};	
	pid = fork();

	switch(pid){
	case -1:
		printf("fork error \n");
		exit(1);

	case 0:
		if(a==1)
			execl("/bin/ls",argv,"-al",0);
		if(a==0)
			execl("/bin/ls",argv,0);
		printf("exec error \n");
		exit(1);

	default:
		wait(status);	}
	return 0;}
