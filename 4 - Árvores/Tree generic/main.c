//  gcc main.c Treeg.c -c
//  gcc main.o Treeg.o

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "Treeg.h"

void print(void *a)
{
	char *c = (char *)a;
	printf("%c ", *c);
}

int compar_char(void *a, void *b)
{
	return *((char *)a) - *((char *)b);
}

int main()
{
	char c[] = "abcdez";
	Tree *t = Tree_alloc(&c[0],
						 Tree_alloc(&c[1], NULL, NULL), NULL);

	Tree_print(t, print);
	printf("\n\n\n");


	/*
	Tree *tt = Tree_alloc('a',
						  Tree_alloc('b',
									 NULL,
									 Tree_alloc('d', NULL, NULL)),
						  Tree_alloc('c',
									 Tree_alloc('e', NULL, NULL),
									 Tree_alloc('f', NULL, NULL)));
	*/

	Tree *t1 = Tree_alloc("d", NULL, NULL);
	Tree *t2 = Tree_alloc("b", NULL, t1);
	Tree *t3 = Tree_alloc("e", NULL, NULL);
	Tree *t4 = Tree_alloc("f", NULL, NULL);
	Tree *t5 = Tree_alloc("c", t3, t4);
	Tree *t0 = Tree_alloc("a", t2, t5); // raiz.

	Tree_print(t5, print); // mostra a subarvore C.
	printf("\n");
	Tree_print(Tree_getLeft(t5), print); // mostra filho a esquerda da subarvore C.
	printf("\n");

	Tree_print(t4, print); // mostra a subarvore F.
	printf("\n");
	Tree_setLeft(t4, "z");
	Tree_print(t4, print); // adiciona um no a esquerda da subarvore F com dois filhos NULL.
	printf("\n");

	printf("== Arvore ==\n");
	Tree_print(t0, print); // mostra a arvore.
	printf("\n");

	Tree_free(t);
	return 0;
}
