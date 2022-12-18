//  gcc Stack.c main.c -c
//  gcc Stack.o main.o

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Stack.h"

// funcao print generic - converte void para int
void print(void *a)
{
	int *v = (int *)a;
	printf("%d ", *v);
}

// funcao generica de comparacao
int compar(void *a, void *b)
{
	int aux = 2;
	if (*((int *)a) == *((int *)b))
		aux = 0;
	if (*((int *)a) > *((int *)b))
		aux = 1;
	if (*((int *)a) < *((int *)b))
		aux = -1;
	return aux;
}

int main()
{
	int n[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	Stack *s = Stack_alloc(8);

	printf("Empilhando:\n");
	Stack_push(s, &n[0]);
	Stack_push(s, &n[1]);
	Stack_push(s, &n[2]);
	Stack_push(s, &n[3]);
	Stack_push(s, &n[4]);
	Stack_push(s, &n[5]);
	Stack_print(s, print);

	printf("\nDesempilhando 3x:\n");
	Stack_pop(s);
	Stack_pop(s);
	Stack_pop(s);
	Stack_print(s, print);

	printf("\nElemento no topo da pilha: ");
	print(Stack_top(s));

	printf("\nTamanho da pilha: %d ", Stack_length(s));

	Stack_free(s);
	return 0;
}

/*
typedef struct {
	char nome[20];
	int mundiais;
} Time;

void printTime(void *a) {
	Time *t = (Time*)a;
	printf("%s %d", t->nome, t->mundiais);
}


int main() {
	Time times[] = {{"Sao Paulo",3},
					{"Corinthians",2},
					{"Palmeiras",0},
					{"Flamengo",1}};
	Stack *s = Stack_alloc(20);
	Stack_push(s, &times[0]);
	Stack_push(s, &times[1]);
	Stack_push(s, &times[2]);
	Stack_push(s, &times[3]);
	Stack_print(s, printTime);
	Stack_free(s);

	return 0;
}
*/
