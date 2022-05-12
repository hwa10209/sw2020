#define A_ROW 3
#define A_COL 3
#define B_ROW 3
#define B_COL 3
#include <sys/time.h>
#define MILLION 1000000
#include <stdio.h>

void main(){
	struct timeval tpstart, tpend;
    long timediff;
   
	int i, j, k;
	static int a[A_ROW][A_COL]={{1,3,5},{7,9,11},{13,15,17}};
	static int b[B_ROW][B_COL]={{2,4,6},{8,10,12},{14,16,18}};
	static int c[A_ROW][B_COL];
	
	printf("<Matrix A>\n");
	for(i=0;i<A_ROW;i++){
		for(j=0;j<B_COL; j++){
			printf("%4d", a[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	printf("<Matrix B>\n");
   	for(i=0;i<A_ROW;i++){
		 for(j=0;j<B_COL; j++){
			printf("%4d", b[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	
	gettimeofday(&tpstart, NULL);

    for (i = 0; i < A_ROW; i++){
		for (j = 0; j < B_COL; j++){
			for (k = 0; k < A_COL; k++){
			     c[i][j] += a[i][k]*b[k][j];
			}
		}
	}

    gettimeofday(&tpend, NULL);

	printf("<Matrix A> X <Matrix B> with single processor.\n");
	for (i = 0; i < A_ROW; i++){
		for (j = 0; j < B_COL; j++){
			printf("%4d", c[i][j]);
	    }
	     printf("\n");
	}
	printf("\n");

	timediff = MILLION*(tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec - tpstart.tv_usec;

    printf("It took %ld micro sec \n", timediff);
}

