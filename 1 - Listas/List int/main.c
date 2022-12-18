//  gcc List.c main.c -c
//  gcc List.o main.o

#include <stdlib.h>
#include <stdio.h>
#include "List.h"

int main()
{
	List *l = List_alloc();

	List_insert(l, 0);
	List_insert(l, 1);
	List_insert(l, 2);
	List_insert(l, 3);
	List_insert(l, 4);
	List_insert(l, 5);
	List_insert(l, 6);
	List_insert(l, 7);

	printf("\n-----Lista-----\n");
	List_print(l);

	printf("Tamanho da lista = %d\n", List_getLenght(l));
	// printf("cont: %d\n\n",List_count(l));

	printf("\n-----Invertendo_a_lista-----\n");
	List_invert(l);
	List_print(l);

	printf("\n---Remove_elemendo(0)_da_lista---\n");
	List_remove(l, 0);
	List_print(l);

	printf("\n-----Ordenando_lista-----\n");
	l = List_qsort(l);
	List_print(l);

	printf("\n-Adiciona_elemendo(10)_na_lista_de_forma_ordenada.\n");
	List_insertSorted(l, 10);
	List_print(l);

	printf("\n-----Lista-----\n");
	List_print(l);
	printf("Maior elemento removido = %d\n", List_removeMax(l));
	printf("----Lista-Depois----\n");
	List_print(l);

	printf("\n----Concatenando_Listas----\n");
	List *l1 = List_alloc();
	List_insert(l1, 1);
	List_insert(l1, 3);
	List_insert(l1, 5);

	printf("L1 = ");
	List_print(l1);

	List *l2 = List_alloc();
	List_insert(l2, 2);
	List_insert(l2, 4);
	List_insert(l2, 6);

	printf("L2 = ");
	List_print(l2);

	List_concat(l1, l2);
	printf("L3 = ");
	List_print(l1);

	List_free(l);
	return 0;
}
