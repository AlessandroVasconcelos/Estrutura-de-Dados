//  gcc Queue.c main.c -c
//  gcc Queue.o main.o

#include <stdlib.h>
#include <stdio.h>
#include "Queue.h"

int main()
{
	Queue *q = Queue_alloc(6); // 6 elementos int add na fila

	Queue_push(q, 1);
	Queue_push(q, 2);
	Queue_push(q, 3);
	Queue_push(q, 4);
	Queue_push(q, 5);
	Queue_push(q, 6);
	// Queue_push(q, 7); //fila suporta apenas 6 numeros (fila cheia).
	Queue_print(q);

	printf("Remove primeiro elemento da fila (pop) = %d\n\n", Queue_pop(q));

	printf("O numero 7 entra na fila (push)...\n");
	Queue_push(q, 7);
	Queue_print(q);

	printf("\ninicio da fila = %d\n", Queue_begin(q));
	printf("fim da fila = %d\n", Queue_end(q));
	printf("Tamanho da fila = %d\n\n", Queue_length(q));

	Queue_print(q);

	Queue_free(q);
	return 0;
}
