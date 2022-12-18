//  gcc List.c main.c -c
//  gcc List.o main.o

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "List.h"

// print generico para int
void print(void *a)
{
	int *v = (int *)a;
	printf("%d ", *v);
}

// print generico para struct
/*
void print(void *a)
{
	//nome da struct(Usuario)
	Usuario *u = (Usuario*)a;
	printf("%10s %8d\n", u->login, u->senha);
}
*/

// funcao generica de comparacao para int  *((int *)a
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

int compar1(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}

int compar2(const void *a, const void *b)
{
	if (*(int *)a > *(int *)b)
		return 1;
	else if (*(int *)a < *(int *)b)
		return -1;
	else
		return 0;
}

// funcao generica de comparacao para struct
/*
int cmp(void *a, void *b)
{
	Usuario *u = (Usuario*)a;
	char *login = (char*)b;
	return strcmp(u->login, login); //strcmp == strings iguais ou nao.
}
*/

int main()
{
	int n[] = {1, 11, 2, 13, 14, 5, 6, 7, 8, 10, 9, 0, 3, 12, 4}; // tem 15 numeros
	List *l = List_alloc();

	qsort(n, 15, sizeof(int), compar2); // ordena valores
	List_insert(l, &n[7]);
	List_insert(l, &n[6]);
	List_insert(l, &n[5]);
	List_insert(l, &n[4]);
	List_insert(l, &n[3]);
	List_insert(l, &n[2]);
	List_insert(l, &n[1]);
	List_insert(l, &n[0]);

	List_print(l, print);

	List_invert(l);
	List_print(l, print);

	List_removeBegin(l);
	List_removeEnd(l);
	List_print(l, print);

	List_insertBegin(l, &n[0]);
	List_insertEnd(l, &n[7]);
	List_print(l, print);

	List_remove1(l, &n[0], compar); // === List_findAndRemove(l,&n[1],compar) e List_remove(l,&n[0],compar); funciona cadastro.
	List_print(l, print);

	List_find(l, &n[1], compar);
	printf("\ntamanho da lista: %d\n", List_getLenght(l));

	printf("\n----Concatenando_Listas----\n");
	List *l1 = List_alloc();
	List_insert(l1, &n[1]);
	List_insert(l1, &n[3]);
	List_insert(l1, &n[5]);

	printf("L1 = ");
	List_print(l1, print);

	List *l2 = List_alloc();
	List_insert(l2, &n[2]);
	List_insert(l2, &n[4]);
	List_insert(l2, &n[6]);

	printf("L2 = ");
	List_print(l2, print);

	List_concat(l1, l2);
	printf("L3 = ");
	List_print(l1, print);

	List_free(l);
	return 0;
}
