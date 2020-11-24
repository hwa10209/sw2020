#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define   ONE_MEG   1048576

//  Prototypes
void     Memory_allocation(int HEAP_ALLOC , int STACK_ALLOC);
char     *commas(unsigned long amount);


// for heap
unsigned long    FirstHeapLocation;			
long		HeapDepth = 0;	
unsigned long		*MemoryPtr;
long        Temp;
long        *TempPointer;
//for stack
unsigned long*    FirstStackLocation;							
long   		 StackDepth=0;

//  The main code is here
int main(int argc, char *argv[]){
	if(argc<3){
		printf(" Usage: %s <SizeInMegabyte Each in heap><SizeInMegabyte Each in stack>\n",argv[0]);
		exit(1);
	}
	long  		 TopOfStack;
    FirstStackLocation = (unsigned long)(&TopOfStack);
	


	printf("Memory allocating starts!\n");
	int HEAP_ALLOC = atoi(argv[1]);
	int STACK_ALLOC=atoi(argv[2]);
    printf("First location on stack: %s\n", commas(FirstStackLocation));
	FirstHeapLocation =  (unsigned long*) malloc( HEAP_ALLOC*ONE_MEG);
    printf("First location of heap: %s\n", commas(FirstHeapLocation));

    Memory_allocation(HEAP_ALLOC, STACK_ALLOC);
             
	return 0;
}						// End of main

void  Memory_allocation(int HEAP_ALLOC, int STACK_ALLOC )
{
    char    Temp[ STACK_ALLOC*ONE_MEG ];
    char    StringTop[32];
    char    StringBottom[32];
	char 	StringHeap[32];
    strcpy( StringTop,  commas( (unsigned long)(FirstStackLocation) ) );
    strcpy( StringBottom, commas( (unsigned long)&(Temp[STACK_ALLOC*ONE_MEG]) ) );
    printf("Iteration = %3d: Stack Bottom : %s  \n", 
             StackDepth, StringBottom);

 
   	MemoryPtr = (unsigned long * ) malloc( HEAP_ALLOC*ONE_MEG );
																//Heap_allocation
  // strcpy( StringHeap,  commas(MemoryPtr) );		
	printf("Heap : %s  \n",commas(MemoryPtr));   

	TempPointer = MemoryPtr;
	 // Write to each page in the megabyte
	    while ( (unsigned long)TempPointer < (unsigned long)((long)MemoryPtr + ONE_MEG) )  {
                TempPointer[0] = Temp;
                TempPointer = (long *)((unsigned long)TempPointer +4096);
            }          

	StackDepth++;
    Memory_allocation(HEAP_ALLOC, STACK_ALLOC );
 	
 }


///////////////////////////////////////////////////////////////////////////
//  The following routines are for formatting only and aren't needed for
//  an understanding of the memory manipulations done above.
///////////////////////////////////////////////////////////////////////////
#define BASE 16
#define GROUP 4
// This routine converts an unsigned integer into a string with commas.
// You may need to adjust the base and the number of digits between
// commas as given by BASE and GROUP.
// Need space to hold the digits of an unsigned int,
// intervening commas and a null byte. It depends on
// BASE and GROUP above (but logarithmically, not
// as a constant. so we must define it manually here)
///////////////////////////////////////////////////////////////////////////
#define MAXTEXT 25 

int prepend(char *, unsigned, char *);
int preprintf(char *, unsigned, char *, ...);

char *commas(unsigned long amount)
    {
    short i;
    short offset = MAXTEXT-1;   /* where the string "starts"  */
    short place;                /* the power of BASE for      */
                                /* current digit              */
    static char text[MAXTEXT];

    for ( i = 0; i < MAXTEXT; i++ )
        text[i] = '\0';
					     
   /* Push digits right-to-left with commas */
   for (place = 0; amount > 0; ++place)
      {
      if (place % GROUP == 0 && place > 0)
         offset = prepend(text,offset,",");
      offset = preprintf(text,offset,"%X",amount % BASE);
      amount /= BASE;
    }
    return (offset >= 0) ? text + offset : NULL;
}
    /* preprint.c: Functions to prepend strings */
    
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
    
int prepend(char *buf, unsigned offset, char *new_str)
    {
    int new_len = strlen(new_str);
    int new_start = offset - new_len;
    /* Push a string onto the front of another */
    if (new_start >= 0)
        memcpy(buf+new_start,new_str,new_len);
    
    /* Return new start position (negative if underflowed) */
    return new_start;
}
    
int preprintf(char *buf, unsigned offset, char *format, ...)
    {
    int pos = offset;
    char *temp = malloc(BUFSIZ);
    
    /* Format, then push */
    if (temp)
        {
        va_list args;
        
        va_start(args,format);
        vsprintf(temp,format,args);
        pos = prepend(buf,offset,temp);
        va_end(args);
        free(temp);
    }
    return pos;
}
