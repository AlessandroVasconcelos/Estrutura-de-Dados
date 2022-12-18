//  gcc Stack.c main.c -c
//  gcc Stack.o main.o

#include <stdlib.h>
#include <stdio.h>
#include "Stack.h"

int main()
{
	Stack *s = Stack_alloc(20);

	Stack_push(s, 7);
	Stack_push(s, 3);
	Stack_push(s, 19);
	Stack_push(s, 21);
	Stack_push(s, 2);
	Stack_push(s, 8);

	printf("Tamanho da pilha = %d\n", Stack_length(s));
	printf("Topo da pilha = %d\n", Stack_top(s));
	Stack_print(s);

	printf("------------------------------------------------");
	printf("\n Remove elemento do topo da pilha (pop) = %d\n", Stack_pop(s));
	Stack_print(s);

	Stack_free(s);
	return 0;
}
