//test_app.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define MAX_SIZE 1	

int main(void) {
	printf("choose the length of word // 1: 10, 2: 110\n");
	int choose;
	scanf("%d",&choose);
	gets();
	int fd;
	char *one, *two;
	char* in = (char*)malloc(sizeof(char) * MAX_SIZE);
	char* out = (char*)malloc(sizeof(char) *200);
	switch(choose){
		case 1:
			strcpy(out,"abcdEFGH12");
			//strcpy(out,*one);
			break;
		case 2:
			strcpy(out,"aaaaaaaa11bbbbbbbb22cccccccc33dddddddd44eeeeeeee55ffffffff66gggggggg77hhhhhhhh88iiiiiiii99jjjjjjjj00kkkkkkkk11");
			//strcpy(out,*one);
			break;
	}
	printf("<change this>\n%s\n---------------------------------\n",out);

	if ((fd = open("/dev/mydevicefile", O_RDWR)) < 0) {
		perror("open error");
		return -1;
	}

	 

	for(int i = 0; i<strlen(out); i++){	
		write(fd,out+i , MAX_SIZE);
	}
	for(int i = 0; i<strlen(out) && i<100; i++){
		read(fd, in, MAX_SIZE);
		printf("%s", in);	
		
	}
	printf("\n");

	free(in);
	free(out);

	close(fd);
	return 0;
}
