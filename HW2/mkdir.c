#include "instructions.h"

int mkdir(char *b){
	int pid, status;
	char* argv[]={"mkdir",b,0};

	pid=fork();

	switch(pid){
	case -1:
		printf("fork error \n");
		exit(1);
	
	case 0:
		execv("/bin/mkdir",argv);
		printf("exec error \n");
		exit(1);
	
	default:
		wait(&status);
	}
	return 0;
}
