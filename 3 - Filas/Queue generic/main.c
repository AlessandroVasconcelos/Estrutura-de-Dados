//  gcc Queue.c main.c -c
//  gcc Queue.o main.o

#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include "Queue.h"

// funcao print generic - converte void para int
void printInt(void *a) 
{
	int *num = (int*)a;
	printf("%d ", *num);
}

//print generico para struct
/*
void print(void *a)
{
    //nome da struct(Usuario)
	Usuario *u = (Usuario*)a;
	printf("%10s %8d\n", u->login, u->senha);
}
*/


int main()
{
	int n[] = {0,1,2,3,4,5,6,7,8,9,10};
    	Queue *q = Queue_alloc(6);
	Queue_push(q, &n[6]);
	Queue_push(q, &n[5]);
	Queue_push(q, &n[4]);
	Queue_push(q, &n[3]);
	Queue_push(q, &n[2]);
	Queue_push(q, &n[1]);
	
	printf("Tamanho da fila: %d\n\n",Queue_length(q));
	Queue_print(q, printInt);
	
	Queue_pop(q);
    	Queue_print(q, printInt);
    	Queue_pop(q);
   	Queue_print(q, printInt);
   	Queue_pop(q);
    	Queue_print(q, printInt);
    	Queue_pop(q);
    	Queue_print(q, printInt);
    	Queue_pop(q);
    	Queue_print(q, printInt);
	
    	return 0;
}

/*
int main()
{
	Queue *q = Queue_alloc(6);
	int n[] = {1,2,3,4,5,6,7}, i;
	for (i=0; i<7; i++)
		Queue_push(q, &n[i]);
	Queue_print(q, printInt);
	
	printf("removido = ");
	printInt(Queue_pop(q));
	printf("\n");
	
	Queue_push(q, &n[6]);
	Queue_print(q, printInt);
	
	printf("inicio = ");
	printInt(Queue_begin(q));
	printf("\n");
	
	printf("final = ");
	printInt(Queue_end(q));
	printf("\n");
	
	Queue_print(q, printInt);
	
	Queue_free(q);
	return 0;
}
*/
