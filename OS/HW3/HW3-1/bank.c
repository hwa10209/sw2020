#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

volatile long balance = 100;

void *deposit();
void *withdraw();

int main()
{
	pthread_t dep[100],wit[100];
	int retval;
	int i;
	printf("With 1 won, deposit & withdraw 1 won 500 times each with 100threads \n");
	

	for(i=0;i<100;i++){
		pthread_create(&dep[i],NULL,deposit,NULL);

		pthread_create(&wit[i],NULL,withdraw,NULL);

	}
	for(i=0; i<100;i++){
		pthread_join(dep[i],NULL);

		pthread_join(wit[i],NULL);

	}
	printf("after work balance= %d won\n", balance);
	return 0;
}

void *deposit()
{
	for(int j=0;j<500;j++){
	balance+=1;
	}
	pthread_exit(0);
}

void *withdraw()
{
	for(int j=0;j<500;j++){
	balance-=1;
	}
	pthread_exit(0);
}
