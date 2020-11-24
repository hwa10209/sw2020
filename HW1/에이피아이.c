//에이피아이.c
#include "StackQueue.h"


STACK* create_stack(){											//Stack 만들기.
	STACK* stack = (STACK*)malloc(sizeof(STACK));
	if(!stack)
		return 0;
	stack-> count = 0;
	stack ->top = NULL;
	return stack;}
int push(STACK* stack, void* in){								//push 함수
	STACK_NODE* node = (STACK_NODE*)malloc(sizeof(STACK_NODE));	
	if(!node)
		return 0;
	node->data_ptr = in;
	node->link = stack->top;
	stack->top = node;
	stack->count++;
	return 1;}
void* pop(STACK* stack){										//pop 함수
	STACK_NODE* temp = stack->top;
	void* data_out = stack->top->data_ptr;
	stack ->top = stack->top->link;
	free(temp);
	(stack->count)--;
	return data_out;}
void playstack(){										//stack을 과정별로 실행
STACK* sta= create_stack();
	printf("stack sta 생성 완료\n");
	int  menu=0;
	char delim[] =" ";
	char* str =(char*)malloc(sizeof(char)*100);
	char* token;
	while(!(menu==3)){
		printf("\n..................................\n");
		printf("메 뉴(1)PUSH (2)POP+출력 (3)EXIT \n");
		scanf("%d", &menu);									//동작선택.
		__fpurge(stdin);
	switch(menu)
	{
		case 1: 
			printf("숫자 다섯개를 한줄입력하세요.(100자 이내)\n");
			scanf("%[^\n]s",str);							
			__fpurge(stdin);
			token = strtok(str, delim);
			while(token != NULL){
				push(sta, token);					//token의 숫자들을 push
				token = strtok(NULL, delim);
			}
			printf("push 완료!\n");
			break;
		case 2: 
			printf("\n");
			for(int i=0; i<5; i++)
				printf("%s ",((char*)pop(sta)));			//pop을 5번 수행
			printf("\npop 완료!\n");
			break;
		case 3: 
			menu = 3;   
			printf("\n종료합니다!");
			printf("\n..................................\n");
			break;
		default:
			printf("?"); break;
		}
	}
	free(str);
}
QUEUE* CreateQueue(){										//queue 만들기
	QUEUE *pNewQueue = (QUEUE*)malloc(sizeof(QUEUE));
	if(pNewQueue ==NULL)
		return NULL;
	pNewQueue->count=0;
	pNewQueue->front =pNewQueue->rear=NULL;
	return pNewQueue;}
int Enqueue(QUEUE* pQueue, void* item){						//enqueue 함수
	QUEUE_NODE *pNewNode = (QUEUE_NODE*)malloc(sizeof(QUEUE));
	if(pNewNode==NULL)								//메모리자리 없을 수 도있음
		return 0;
	pNewNode->data_ptr = item;								
	pNewNode->next = NULL;
	if(pQueue ->count <=0)
		pQueue ->front = pQueue ->rear = pNewNode;
	else{
		pQueue->rear->next=pNewNode;
		pQueue->rear = pNewNode;
	}
	pQueue->count++;
}
void* Dequeue(QUEUE *pQueue){								//dequeue 함수
	QUEUE_NODE* pFront = NULL;
	void* item = 0;
	if(pQueue->count <=0)
		return 0;
	pFront = pQueue ->front;
	item = pFront->data_ptr;
	if(pQueue->count == 1)									//하나남았을 경우.
		pQueue->front = pQueue->rear = NULL;
	else
		pQueue->front = pFront->next;
	free(pFront);
	pQueue->count--;
	return item;
}
void playqueue(){										//stack을 과정별로 실행
	QUEUE* que= CreateQueue();
	printf("queue que 생성 완료\n");
	int  menu=0;
	char delim[] =" ";
	char* str =(char*)malloc(sizeof(char)*100);
	char* token;
	while(!(menu==3)){
		printf("\n..................................\n");
		printf("메 뉴 (1)ENQUEUE (2)DEQUEUE+출력 (3)EXIT \n");
		scanf("%d", &menu);									//동작선택.
		__fpurge(stdin);
	switch(menu)
	{
		case 1: 
			printf("숫자 다섯개를 한줄입력하세요.(100자 이내)\n");
			scanf("%[^\n]s",str);
			__fpurge(stdin);
			token = strtok(str, delim);
			while(token != NULL){
				Enqueue(que, token);			//token에 있는 숫자들 enqueue
				token = strtok(NULL, delim);
			}
			printf("enqueue 완료!\n");
			break;		
		case 2: 
			printf("\n");
			for(int i=0; i<5; i++)
				printf("%s ",((char*)Dequeue(que)));		//dequeue 5번 수행.
			printf("\ndequeue 완료!\n");
			break;
		case 3: 
			menu = 3;   
			printf("\n종료합니다!");
			printf("\n..................................\n");
			break;
		default:
			printf("?"); break;
		}
	}
	free(str);
}
