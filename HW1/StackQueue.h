//StackQueue.h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#define NULL ((void *)0)

typedef struct snode{
	void* data_ptr;
	struct snode* link;
}STACK_NODE;

typedef struct stack{
	int count;
	STACK_NODE* top;
}STACK;

STACK* create_stack();
int push(STACK* stack, void* in);
void* pop(STACK* stack);
void playstack();
typedef struct qnode{
	void* data_ptr;
	struct qnode* next;
}QUEUE_NODE;

typedef struct queue{
	int count;
	QUEUE_NODE *front, *rear;
}QUEUE;

QUEUE* CreateQueue();
int Enqueue(QUEUE* pQueue, void* in);
void* Dequeue(QUEUE *pQueue);
void playqueue();
