#include "instructions.h"

int pwd() {
	int pid, status;
	char* argv[] = { "pwd", 0 };
	pid = fork(); 

	switch (pid) {
	case -1:
		printf("fork error \n");
		exit(1);

	case 0:
		execv("/bin/pwd", argv); 
		printf("exec error \n");
		exit(1);

	default:
		wait(&status);
	}

	return 0;
}
