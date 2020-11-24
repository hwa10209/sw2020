#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "instructions.h"
#define size 10

int main()
{
	char str[size]; 

	printf("+++++++++++++++++++++ MyShell ++++++++++++++++++\n");
	printf("ls (ls -al), mkdir, pwd, exit\n");

	while (true)
	{
		printf("-> ");
		gets(str);

        if (!strcmp("pwd", str))	//check current directory(Given code)
			pwd();

		if (!strcmp("ls -al",str))	//check current directory's list all
			ls(1);
		
		if (!strcmp("ls", str))		//chaeck current directory's list
			ls(0);

		if (!strncmp("mkdir",str,5))//make directory with following title
		{
			char *ptr = strtok(str," ");
			ptr=strtok(NULL," ");
			mkdir(ptr);
		}
		if (!strcmp("exit", str))	//exit Myshell
			break;
	}

	return 0;
}
