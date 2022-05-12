/* Pleas read this,,
 *
 * This source file should use input file
 * Each input files should contain elements and maximum weight, -1
 * The input.txt file can be used for mode 1,2,3
 *
 * input.txt example)
 * 2 3
 * 3 4
 * 4 6
 * 5 7
 * 8 -1
 *
 * The input_challenge.txt file can be used only for mode 4(challenge)
 *
 * input_challenge.txt example)
 * 2 3
 * 3 4
 * 4 6
 * 5 7
 * 8 7 -1
 *
 * File's name is not important but the file you can use (to play each mode)
 * depends on the format of the last line of the file
 *
 * so when you use normal input file you should play only 1,2,3 mode(one mode at one check)
 * or when you use challenge input file you should play only 4 mode.
 *
 */

#include <stdio.h>
#include <stdlib.h>
static int Numelement=0, Maxweight,Maxweight2;

void print( int A[][2] )
{
  int i;

  for (i=0; i<Numelement; i++)
  {
    printf("(");
	printf("%d, %d",A[i][0], A[i][1]);
	printf(") ");
    printf("\n");
  }
  printf("Maxweight = %d\n",Maxweight);
  if(Maxweight2 !=0)
	printf("secondMaxweight = %d\n",Maxweight2);

}


int *readkeys( const char infile[] )
  // returns an array of int integers, with its size stored in
  // the memory indicated by integer pointer variable pN
  // the retured memory should freed by the caller
{
  int *A, tmp,tmpw,tmpb;
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
	  //find Maximum weight and Number of elements
	do{
		if ( fscanf(fp, "%d", &tmp) != 1 ) {
		  fprintf(stderr, "wrong elements %s\n",infile);
		  return NULL;
		}
		if(tmp==-1)
			Numelement--;
		else
		{
			Maxweight=tmp;
			if ( fscanf(fp, "%d", &tmp) != 1) {
			  fprintf(stderr, "wrong elements %s\n",infile);
			  return NULL;
			}
			if(tmp != -1){
				Numelement++;
				Maxweight2=tmp;
			}
			else
				Maxweight2=0;
		}
	}while(tmp !=-1);

  }
  fclose(fp);


    //get weight and values
  fp = fopen(infile,"r");
  A = (int*)malloc(sizeof(int)*(Numelement*2));
  for (i=0; i<Numelement*2;) {
	fscanf(fp, "%d", &tmpw);
	fscanf(fp, "%d", &tmpb);
	A[i]=tmpw; i++;
	A[i]=tmpb; i++;
  }
  fclose(fp);
  return A;
}


int main()
{
  int *A;	// to store data to be sorted
  int j,mode;
  /* for file name, max length 1023 including path */
  char infile[1024];

  while(1){
	  Numelement=Maxweight=Maxweight2=0;
	  /* file name given by keyboard */
	  printf("Input file name? :");
	  scanf("%s",infile);
	  A = readkeys(infile);
	  printf("Mode number? 1,2,3,4 :");
	  scanf("%d",&mode);
	  /* read text file of integers */
	  //mode 1,2,3 can use the same file,
	  //but mode 4' input file should be different with (mode 1,2,3)'s
	  if(mode==1 || mode==2 || mode==3)
	  {
		  if(Maxweight2 !=0)
		  {
			  printf("Your mode is one of 1,2,3, but you have chosen file for mode4(challenge)!\n ");
			  return 0;
		  }
	  }
	  else if(mode==4)
	  {
		  if(Maxweight2 ==0)
		  {
			  printf("Your mode is 4(challenge), but you have chosen file for mode 1,2,3 !\n");
			  return 0;
		  }
	  }
	  else{
		  printf("You should choose one integer from 1,2,3,4\n");
		  return 0;
	  }
	  int Element[Numelement][2];


	  if ( A != NULL && Numelement > 0 ){
		for(j=0; j<Numelement*2;)
		 {
			Element[j/2][0]=A[j]; j++;	//Element's weight
			Element[j/2][1]=A[j]; j++;	//Element's value
		  }
		// print all if not too many
		if ( Numelement < 10 )
		  print(Element);
		printf("%d elements have been loaded.\n",Numelement);
		printf("------------------------------------\n");
//mode 1
		switch(mode){
		case 1:
		    {
			int Benefit[Numelement+1][Maxweight+1][Numelement+1];		//Benefit[][][0] :value ,fBenefit[][][1~]
															//keep used element
			int i,w,t1;
			for(w = 0; w<=Maxweight;w++)
				Benefit[0][w][0] = Benefit[0][w][1] = 0;
			for(i = 0; i<=Numelement;i++)
				Benefit[i][0][0] = Benefit[i][0][1]  = 0;

			for(i=1;i<=Numelement;i++){
				for(w=1; w<=Maxweight;w++){
					if(Element[i-1][0]<=w){
						if(Element[i-1][1]+Benefit[i-1][w-Element[i-1][0]][0]>Benefit[i-1][w][0]){
							Benefit[i][w][0] = Element[i-1][1]+Benefit[i-1][w-Element[i-1][0]][0];
							for(t1=1;t1<i;t1++)
								Benefit[i][w][t1] = Benefit[i-1][w-Element[i-1][0]][t1];
							Benefit[i][w][i] = 1;
						}
						else{
							Benefit[i][w][0] = Benefit[i-1][w][0];
							for(t1=1;t1<i;t1++)
								Benefit[i][w][t1] = Benefit[i-1][w][t1];
						}
					}
					else{
						Benefit[i][w][0] = Benefit[i-1][w][0];
						for(t1=1;t1<i;t1++)
							Benefit[i][w][t1] = Benefit[i-1][w][t1];
					}
				}
			}
			for(w = 0; w<=Maxweight;w++){
				for(i=0;i<=Numelement;i++)
					printf("%5d ",Benefit[i][w][0]);
			printf("\n");
			}
			printf("------------------------------------\n");
			printf("1.0-1 knapsack. \n");
			for(t1=1;t1<=Numelement;t1++)
			{
				if(Benefit[Numelement][Maxweight][t1]==1)
					printf(" %d",t1);
			}
				printf("  %d\n\n",Benefit[Numelement][Maxweight][0]);

			break;
		}
//mode 2
		case 2:
		    {
			double fBenefit[Numelement+1][Maxweight+1][Numelement+1];		//fBenefit[][][0] :value, fBenefit[][][1~]
															//keep element


			int i,w,t2;
			int temp=0;
			for(w = 0; w<=Maxweight;w++)
				fBenefit[0][w][0] = fBenefit[0][w][1]  =  0;
			for(i = 0; i<=Numelement;i++)
				fBenefit[i][0][0] = fBenefit[i][0][1]  =  0;

			for(i=1;i<=Numelement;i++){
				for(w=1; w<=Maxweight;w++){
					if(Element[i-1][0]<=w){
						if(Element[i-1][1]+fBenefit[i-1][w-Element[i-1][0]][0]>fBenefit[i-1][w][0]){
							fBenefit[i][w][0] = Element[i-1][1]+fBenefit[i-1][w-Element[i-1][0]][0];
							for(t2=1;t2<i;t2++)
								fBenefit[i][w][t2] = fBenefit[i-1][w-Element[i-1][0]][t2];
							fBenefit[i][w][i] = 1;
						}
						else{
							fBenefit[i][w][0] = fBenefit[i-1][w][0];
							for(t2=1;t2<i;t2++)
								fBenefit[i][w][t2] = fBenefit[i-1][w][t2];
						}
					}
					else if(0.5*Element[i-1][0]<=w && fBenefit[i-1][w-Element[i-1][0]][i-1]!=0.5){
						if(0.5*Element[i-1][1]+fBenefit[i-1][(int)(w-0.5*Element[i-1][0])][0]>fBenefit[i-1][w][0]){
							fBenefit[i][w][0] = 0.5*Element[i-1][1]+fBenefit[i-1][(int)(w-0.5*Element[i-1][0])][0];
							for(t2=1;t2<i;t2++)
								fBenefit[i][w][t2] = fBenefit[i-1][(int)(w-0.5*Element[i-1][0])][t2];
							fBenefit[i][w][i] = 0.5;
						//	temp = i;
						}
						else{
							fBenefit[i][w][0] = fBenefit[i-1][w][0];
							for(t2=1;t2<i;t2++)
								fBenefit[i][w][t2] = fBenefit[i-1][w][t2];
						}
					}
					else{
						fBenefit[i][w][0] = fBenefit[i-1][w][0];
						for(t2=1;t2<i;t2++)
							fBenefit[i][w][t2] = fBenefit[i-1][w][t2];
					}
				}
			}
			for(w = 0; w<=Maxweight;w++){
				for(i=0;i<=Numelement;i++)
					printf("%5.1f ",fBenefit[i][w][0]);
			printf("\n");
			}
			printf("------------------------------------\n");
			printf("2. 0-1 knapsack with one item split.\n");

			for(t2=1;t2<=Numelement;t2++){
				if(fBenefit[Numelement][Maxweight][t2]==0.5)
					temp=t2;
			}
			if(temp!=0)
				printf(" %dX0.5",temp);
			else
				printf("0X0.5(split not used)  ");

			for(t2=1;t2<=Numelement;t2++){
				if((int)fBenefit[Numelement][Maxweight][t2]==1)
					printf(" %d",t2);
			}
			//remove the lower part of the decimal point if the half element's value was not odd
			if((fBenefit[Numelement][Maxweight][0]-(int)fBenefit[Numelement][Maxweight][0])>0)
				printf("  %.1f\n",fBenefit[Numelement][Maxweight][0]);
			else
				printf("  %d\n\n",(int)fBenefit[Numelement][Maxweight][0]);

			break;
		    }
//mode 3

		case 3:
		    {
			int dBenefit[Numelement+1][Maxweight+1][Numelement+1];		//Benefit[][][0] :value ,fBenefit[][][1~]
															//keep used element
			int i,w,t3;
			int temp=0;

			for(w = 0; w<=Maxweight;w++)
				dBenefit[0][w][0] = dBenefit[0][w][1] = 0;
			for(i = 0; i<=Numelement;i++)
				dBenefit[i][0][0] = dBenefit[i][0][1]  = 0;

			for(i=1;i<=Numelement;i++){
				for(w=1; w<=Maxweight;w++){
					if(2*Element[i-1][0]<=w && dBenefit[i-1][w-Element[i-1][0]][i-1] !=2){
						if(2*Element[i-1][1]+dBenefit[i-1][w-2*Element[i-1][0]][0]>dBenefit[i-1][w][0]){
							dBenefit[i][w][0] = 2*Element[i-1][1]+dBenefit[i-1][w-2*Element[i-1][0]][0];
							for(t3=1;t3<i;t3++)
								dBenefit[i][w][t3] = dBenefit[i-1][w-2*Element[i-1][0]][t3];
							dBenefit[i][w][i] = 2;
						}
						else{
							dBenefit[i][w][0] = dBenefit[i-1][w][0];
							for(t3=1;t3<i;t3++)
								dBenefit[i][w][t3] = dBenefit[i-1][w][t3];
						}
					}
					else if(Element[i-1][0]<=w){
						if(Element[i-1][1]+dBenefit[i-1][w-Element[i-1][0]][0]>dBenefit[i-1][w][0]){
							dBenefit[i][w][0] = Element[i-1][1]+dBenefit[i-1][w-Element[i-1][0]][0];
							for(t3=1;t3<i;t3++)
								dBenefit[i][w][t3] = dBenefit[i-1][w-Element[i-1][0]][t3];
							dBenefit[i][w][i] = 1;
						}
						else{
							dBenefit[i][w][0] = dBenefit[i-1][w][0];
							for(t3=1;t3<i;t3++)
								dBenefit[i][w][t3] = dBenefit[i-1][w][t3];
						}
					}
					else{
						dBenefit[i][w][0] = dBenefit[i-1][w][0];
						for(t3=1;t3<i;t3++)
							dBenefit[i][w][t3] = dBenefit[i-1][w][t3];
					}
				}
			}
			for(w = 0; w<=Maxweight;w++){
				for(i=0;i<=Numelement;i++)
					printf("%5d ",dBenefit[i][w][0]);
			printf("\n");
			}
			printf("------------------------------------\n");
			printf("3.0-1 knapsack with one duplicate item.\n");

			for(t3=1;t3<=Numelement;t3++){
				if(dBenefit[Numelement][Maxweight][t3]==2)
					temp=t3;
			}
			if(temp!=0)
				printf(" %dX2",temp);
			else
				printf("0X2(duplicate not used)  ");

			for(t3=1;t3<=Numelement;t3++)
			{
				if(dBenefit[Numelement][Maxweight][t3]==1)
					printf(" %d",t3);
			}
				printf("  %d\n\n",dBenefit[Numelement][Maxweight][0]);

			break;
		}
//mode 4(challenge)
		case 4:
	    {
		int tBenefit[Numelement+1][Maxweight+1][Numelement+1];		//Benefit[][][0] :value ,fBenefit[][][1~]
																	//keep used element
		int i,w,t4;

		for(w = 0; w<=Maxweight;w++)
			tBenefit[0][w][0] = tBenefit[0][w][1] = 0;
		for(i = 0; i<=Numelement;i++)
			tBenefit[i][0][0] = tBenefit[i][0][1]  = 0;

		for(i=1;i<=Numelement;i++){
			for(w=1; w<=Maxweight;w++){
				 if(Element[i-1][0]<=w){
					if(Element[i-1][1]+tBenefit[i-1][w-Element[i-1][0]][0]>tBenefit[i-1][w][0]){
						tBenefit[i][w][0] = Element[i-1][1]+tBenefit[i-1][w-Element[i-1][0]][0];
						for(t4=1;t4<i;t4++)
							tBenefit[i][w][t4] = tBenefit[i-1][w-Element[i-1][0]][t4];
						tBenefit[i][w][i] = 1;
					}
					else{
						tBenefit[i][w][0] = tBenefit[i-1][w][0];
						for(t4=1;t4<i;t4++)
							tBenefit[i][w][t4] = tBenefit[i-1][w][t4];
					}
				}
				else{
					tBenefit[i][w][0] = tBenefit[i-1][w][0];
					for(t4=1;t4<i;t4++)
						tBenefit[i][w][t4] = tBenefit[i-1][w][t4];
				}
			}
		}

		int tBenefit2[Numelement+1][Maxweight2+1][Numelement+1];		//Benefit[][][0] :value ,fBenefit[][][1~]
																	//keep used element

		for(w = 0; w<=Maxweight2;w++)
			tBenefit2[0][w][0] = tBenefit2[0][w][1] = 0;
		for(i = 0; i<=Numelement;i++)
			tBenefit2[i][0][0] = tBenefit2[i][0][1]  = 0;

		for(i=1;i<=Numelement;i++){
			for(w=1; w<=Maxweight2;w++){
				if(tBenefit[Numelement][Maxweight][i]==1){
					tBenefit2[i][w][0] = tBenefit2[i-1][w][0];
					for(t4=1;t4<i;t4++)
						tBenefit2[i][w][t4] = tBenefit2[i-1][w][t4];
				}
				else if(Element[i-1][0]<=w){
					if(Element[i-1][1]+tBenefit2[i-1][w-Element[i-1][0]][0]>tBenefit2[i-1][w][0]){
						tBenefit2[i][w][0] = Element[i-1][1]+tBenefit2[i-1][w-Element[i-1][0]][0];
						for(t4=1;t4<i;t4++)
							tBenefit2[i][w][t4] = tBenefit2[i-1][w-Element[i-1][0]][t4];
						tBenefit2[i][w][i] = 1;
					}
					else{
						tBenefit2[i][w][0] = tBenefit2[i-1][w][0];
						for(t4=1;t4<i;t4++)
							tBenefit2[i][w][t4] = tBenefit2[i-1][w][t4];
					}
				}
				else{
					tBenefit2[i][w][0] = tBenefit2[i-1][w][0];
					for(t4=1;t4<i;t4++)
						tBenefit2[i][w][t4] = tBenefit2[i-1][w][t4];
				}
			}
		}


		for(w = 0; w<=Maxweight;w++){
			for(i=0;i<=Numelement;i++)
				printf("%5d ",tBenefit[i][w][0]);
		printf("\n");
		}
		printf("------------------------------------\n");
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("------------------------------------\n");
		for(w = 0; w<=Maxweight2;w++){
			for(i=0;i<=Numelement;i++)
				printf("%5d ",tBenefit2[i][w][0]);
		printf("\n");
		}
		printf("------------------------------------\n");
		printf("4.0-1 knapsack with two identical knapsack.\n");




		for(t4=1;t4<=Numelement;t4++)
		{
			if(tBenefit[Numelement][Maxweight][t4]==1)
				printf(" %d 1",t4);
			else if(tBenefit2[Numelement][Maxweight2][t4]==1)
				printf(" %d 2",t4);
		}
			printf("  %d\n\n",tBenefit[Numelement][Maxweight][0]+tBenefit2[Numelement][Maxweight2][0]);

		break;
	}
		}
		printf("********************************************************\n");
		printf("******                DONE                       *******\n");
		printf("********************************************************\n");

	  }

  }
}

