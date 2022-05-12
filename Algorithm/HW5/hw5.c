#include <stdio.h>
#include <stdlib.h>
#include <math.h>
static int numElements;
static double distancetable[100][100]={0};
struct PNode{
	int x,y,point;
	struct PNode *next;
};
static struct PNode SortedstructureB[100];
static int cutpoints[7]={0};
static double dFuel[5];
void print( long A[] )
{
  int i;
  for (i=0; i<2*numElements; ){
	  printf("(");
	  printf("%3ld,",A[i]);
	  i++;
	  printf("%3ld",A[i]);
	  i++;
	  printf(") ");
	  if(i%20==0)
		  printf("\n");
  }
}

void printpoints(int points[][101])
{
	int i,j;
	for(j=100; j>=0; j--){
		for(i=0;i<=100;i++)
			printf("%d",points[i][j]);
	printf("\n");
	}
}

void printway(struct PNode* head, double Fuel) //traverse
{
    struct PNode* temp=head;
    double lastx=0,lasty=0,usefuel=0;

    int n;

    for(; head !=NULL;head=head->next){
        usefuel+=sqrt(pow(head->x-lastx,2)+pow(head->y-lasty,2));
        lastx=head->x;       lasty=head->y;
    }
    printf("\n%.0f %.1f\n",Fuel,usefuel);
    head=temp;
    for(; head !=NULL;head=head->next)
    {
       printf("%d %d \n",head->x,head->y);
       lastx=head->x;
       lasty=head->y;
    }
     for(n=0;n<numElements;n++)             //refresh all elements before next way
     {
        SortedstructureB[n].next=NULL;
        SortedstructureB[n].point=1;
     }

}

void DivPointsFuel(int cutnumber, int diff, double fuel)
{
    int i,j;
    for(i=1;i<7;i++)
    {
        if(i>cutnumber || cutpoints[i-1]>=99-(100/(1+cutnumber))-diff)
            cutpoints[i]=99;
        else
            cutpoints[i]=cutpoints[i-1]+(100/(cutnumber+1));
            for(j=cutpoints[i]-diff;j<cutpoints[i]+diff;j++)
            if(abs(SortedstructureB[j].x-SortedstructureB[j].y)<abs(SortedstructureB[cutpoints[i]].x-SortedstructureB[cutpoints[i]].y))
                    cutpoints[i]=j;
    }
    for(i=0;i<6;i++) dFuel[i]=((cutpoints[i+1]-cutpoints[i])/100.0)*fuel;
}
long *readkeys_textfile( const char infile[], int *pN )
{
  long *A, tmp;
  int i;
  FILE *fp;

  // check for input file name
  if ( infile == NULL ) {
    fprintf(stderr, "NULL file name\n");
    return NULL;
  }

  // check for file existence
  fp = fopen(infile,"r");
  if ( !fp ) {
    fprintf(stderr, "cannot open file %s\n",infile);
    return NULL;
  }
  else {
    // check for number of elements
    if ( fscanf(fp, "%d", pN) != 1 || *pN <= 0 ) {
      fprintf(stderr, "cannot read number of elements %s\n",infile);
      return NULL;
    }
    else {
      A = (long*)malloc(sizeof(long)*2*(*pN));
      for (i=0; i<2*(*pN); i++) {
	if ( fscanf(fp, "%ld", &tmp) != 1 ) {
	  fprintf(stderr, "cannot read value at %d/%d\n",i+1,(*pN));
	  *pN = i;	// read data items
	  return A;
	}
	else A[i] = tmp;
      }
    }
    fclose(fp);
    return A;
  }
}


//recursive ������ ���鼭 ���� ���� �ϳ��� ����, 100,100�� ������ return,
//input : ���� ��ǥ,  ���� ���� ����, (��������)���ĵ� ��ǥ��[index].next=memory;
//		���� ��ǥ�� ���� node ����
//return : ��������.  (���̻� �� ���� ������ ����) �����ϸ� null ��ȯ, null �� ������ null ��ȯ, node free
// 100, 100 �̶�� ���� point ��ȯ,�Ǵ� ���� �ּ� ��ȯ, point�� ���� ũ�ٸ� ���� �Ÿ��� ��� ������.

// ��� ����{ x��, y��,point(tree�� level ó��),next}
// ȣ��� �Լ�
//     	��� ����, index�Է�,  node �� ���� next�� null�� �־��
//		���� ���� ��ǥ�� 100,100�̸� ��� ��ȯ,
//			for ������ ������ ���� ��� ������ ��ǥ�鿡 ���� �Լ��� recursive �Լ� ȣ��
//				���� �Ÿ� ���, ���� �ּҷ� �����غ�
//		   		��ȯ�� ����� point�� ���� ũ�� ���� ���� ����(�ִ밪�� ����ϰ� �ִٰ� ����
//				���� ��ü��) , ���� �༮�� point�� ��point�� ����
//
//	���� ������ ������ ��ǥ�� ��� node �� ������� �ʾҴٸ� ������ ���� �ּҴ� null �� ���̰� �����ѳ�,
//		���� node �� free �ϰ� null ��ȯ
//	�ƴ϶�� ���� ��� ��ȯ.
//

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@                fill                     @@@@@

struct PNode* Tryconnect(int index, int index2,double Fuel){
	struct PNode *temp,*memory,*backup;
	double Residue;
	int i,maxpoint=0;
	if(index==index2)			//if current is destination
	    return &SortedstructureB[index2];
	else{							//current is not destination
	    memory=(struct PNode*)malloc(sizeof(struct PNode));
		for(i=index+1;i<index2+1  ;i++)
		{
			Residue=Fuel-distancetable[index][i];
			if(Residue>=0 && Residue-distancetable[i][index2]>=0){
                    temp=Tryconnect(i,index2,Residue);

				if(temp!=NULL && temp->point >=maxpoint){	//keep way if it's better
					maxpoint=temp->point;
                    memory->x=SortedstructureB[index].x;
                    memory->y=SortedstructureB[index].y;
                    memory->point=maxpoint+1;
                    memory->next=temp;
                    backup=memory;
					}
				}
		}
		if(maxpoint ==0){
            free(memory);
			return NULL;
		}
		else
            return backup;
	}

}

//@@@@@@                fill                     @@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@




int main(){

  long *A;	// to store data to be sorted
  /* for file name, max length 1023 including path */
  char infile[1024],outfile[1024];

  /* file name given by keyboard */
   printf("Input file name? ");
   scanf("%s",infile);


   /* read text file of integers:
    * number_of_intergers integer1 integer2 ... */
   A = readkeys_textfile(infile,&numElements);

   if ( A != NULL && numElements > 0 ){
     // print all if not too many
 //    if ( numElements <= 100 )
 //    {
//       print(A);
//       printf("%d Loaded\n", numElements);
//     }

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@                fill                     @@@@@

     int i,j,k,l;                           //put points on array before sorting
     int points[101][101] = {0};
     double Fuel;
     for (i=0; i<2*numElements;){
    	 j=A[i]; i++;
     	 k=A[i]; i++;
     	 points[j][k]+=1;
     }
     free(A);

 //   printpoints(points);

     k=0;                                   //make structures
     for(i=0;i<=100;i++)
    	 for(j=0;j<=100;j++){
            while(points[i][j]>0){
            	SortedstructureB[k].x=i;	//save 'x'
            	SortedstructureB[k].y=j;	//save 'y'
            	points[i][j]--;				//dealing all duplicated points
            	SortedstructureB[k].next=NULL;
                SortedstructureB[k].point=1;
    			 k++;
    		 }
        }
   for(i=0;i<100;i++)                       //make distance table
        for(j=0;j<100;j++)
            distancetable[i][j]=(double)sqrt(pow(SortedstructureB[i].x-SortedstructureB[j].x,2)
                                             +pow(SortedstructureB[i].y-SortedstructureB[j].y,2));

    struct PNode *head;




    Fuel= 200;
    DivPointsFuel(1,8,Fuel);

   //printf("%d %d %d %d %d %d %d\n",cutpoints[0],cutpoints[1],cutpoints[2],cutpoints[3],cutpoints[4],cutpoints[5],cutpoints[6]);

    head=Tryconnect(cutpoints[0],cutpoints[1],dFuel[0]);
    for(i=1;i<6;i++) SortedstructureB[cutpoints[i]].next=Tryconnect(cutpoints[i],cutpoints[i+1],dFuel[i])->next;
    printway(head, Fuel);


     Fuel= 400;
   DivPointsFuel(2,4,Fuel);
 //  printf("%d %d %d %d %d %d %d\n",cutpoints[0],cutpoints[1],cutpoints[2],cutpoints[3],cutpoints[4],cutpoints[5],cutpoints[6]);
    head=Tryconnect(cutpoints[0],cutpoints[1],dFuel[0]);
    for(i=1;i<6;i++) SortedstructureB[cutpoints[i]].next=Tryconnect(cutpoints[i],cutpoints[i+1],dFuel[i])->next;
    printway(head, Fuel);

    Fuel= 600;
      DivPointsFuel(3,3,Fuel);
//    printf("%d %d %d %d %d %d %d\n",cutpoints[0],cutpoints[1],cutpoints[2],cutpoints[3],cutpoints[4],cutpoints[5],cutpoints[6]);
    head=Tryconnect(cutpoints[0],cutpoints[1],dFuel[0]);
    for(i=1;i<6;i++) SortedstructureB[cutpoints[i]].next=Tryconnect(cutpoints[i],cutpoints[i+1],dFuel[i])->next;
    printway(head, Fuel);

    Fuel= 800;
  DivPointsFuel(3,2,Fuel);
//     printf("%d %d %d %d %d %d %d\n",cutpoints[0],cutpoints[1],cutpoints[2],cutpoints[3],cutpoints[4],cutpoints[5],cutpoints[6]);
    head=Tryconnect(cutpoints[0],cutpoints[1],dFuel[0]);
    for(i=1;i<6;i++) SortedstructureB[cutpoints[i]].next=Tryconnect(cutpoints[i],cutpoints[i+1],dFuel[i])->next;
    printway(head, Fuel);

    Fuel= 1000;
  DivPointsFuel(3,1,Fuel);
//  printf("%d %d %d %d %d %d %d\n",cutpoints[0],cutpoints[1],cutpoints[2],cutpoints[3],cutpoints[4],cutpoints[5],cutpoints[6]);
    head=Tryconnect(cutpoints[0],cutpoints[1],dFuel[0]);
    for(i=1;i<6;i++) SortedstructureB[cutpoints[i]].next=Tryconnect(cutpoints[i],cutpoints[i+1],dFuel[i])->next;
    printway(head, Fuel);


    Fuel= 1500;
  DivPointsFuel(4,1,Fuel);
//    printf("%d %d %d %d %d %d %d\n",cutpoints[0],cutpoints[1],cutpoints[2],cutpoints[3],cutpoints[4],cutpoints[5],cutpoints[6]);
    head=Tryconnect(cutpoints[0],cutpoints[1],dFuel[0]);
    for(i=1;i<6;i++) SortedstructureB[cutpoints[i]].next=Tryconnect(cutpoints[i],cutpoints[i+1],dFuel[i])->next;
    printway(head, Fuel);


//@@@@@@                fill                     @@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   }
    return 0;
}




