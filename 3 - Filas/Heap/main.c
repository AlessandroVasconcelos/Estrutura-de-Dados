//  gcc Heap.c main.c -c
//  gcc Heap.o main.o

#include <stdio.h>
#include <stdlib.h>
#include "Heap.h"
#define T 7

int cmp(const void *a, const void *b)
{
	return *((int *)a) - *((int *)b);
}

void print(Heap *h)
{
	int i;
	for (i = 0; i < h->n; i++)
	{
		printf("%d ", *((int *)h->itens[i]));
	}
	printf("\n");
}

int main()
{
	int n[T], i, x, y, m;
	Heap *h, *q;

	printf("Testa Heap_build\n");
	srand(5);
	for (i = 0; i < T; i++)
		n[i] = rand() % 100;
	h = Heap_build(n, T, sizeof(int), cmp);
	print(h);

	printf("Testa Heap_fixUp\n");
	x = 300;
	m = 5;
	Heap_changeValue(h, m, &x);
	print(h);

	printf("Testa Heap_fixDown\n");
	y = -5;
	m = 0;
	Heap_changeValue(h, m, &y);
	print(h);

	Heap_free(h);
	printf("\n");

	printf("Testa Heap_insert\n");
	srand(9);
	for (i = 0; i < T; i++)
		n[i] = rand() % 100;
	q = Heap_alloc(T, cmp);

	for (i = 0; i < T; i++)
		Heap_insert(q, &n[i]);
	print(q);

	printf("Testa Heap_remove\n");
	for (i = 0; i < T; i++)
	{
		Heap_remove(q);
		print(q);
	}

	Heap_free(q);

	return 0;
}
