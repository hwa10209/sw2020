//메인.c
#include "StackQueue.h"

int main()
{
	int Menu=0;
	printf("\n..................................\n");
	printf("메 뉴 (1)STACK (2)QUEUE  \n");
	scanf("%d", &Menu);
	fflush(stdin);

	switch(Menu){
		case 1:
					printf("<stack>\n");
					playstack();						//stack동작 확인.
					break;
		case 2:
					printf("<queue>\n");
					playqueue();						//queue동작 확인.
					break;
		default:	
					printf("잘못된 입력.\n");
					break;
	}
	return 0;

}
