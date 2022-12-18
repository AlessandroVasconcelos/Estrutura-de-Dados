#include <stdlib.h>
#include <stdio.h>
#include "Deque.h"

typedef struct
{
	char nome[20];
	int mundiais;
} Time;

void printTime(void *a)
{
	Time *t = (Time *)a;
	printf("%12s %d\n", t->nome, t->mundiais);
}

// Deque sumulando uma Pilha de times
int main()
{
	Time times[] = {{"Sao Paulo", 3},
					{"Corinthians", 2},
					{"Palmeiras", 0},
					{"Flamengo", 1}};
	Deque *d = Deque_alloc();

	Deque_pushFront(d, &times[0]);
	Deque_pushFront(d, &times[1]);
	Deque_pushFront(d, &times[2]);
	Deque_pushFront(d, &times[3]);

	DequeNode *n = d->back;
	Time *val;
	while (n)
	{
		printTime(n->value);
		n = n->prev;
	}
	printf("\n");

	Deque_free(d);
	return 0;
}
