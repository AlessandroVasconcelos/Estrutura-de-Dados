//  gcc main.c Tree.c -c
//  gcc main.o Tree.o

#include <stdlib.h>
#include <stdio.h>
#include "Tree.h"

int main()
{

	Tree *t = Tree_alloc('+',
						 Tree_alloc('*',
									Tree_alloc('+',
											   Tree_alloc('3', NULL, NULL),
											   Tree_alloc('6', NULL, NULL)),
									Tree_alloc('-',
											   Tree_alloc('4', NULL, NULL),
											   Tree_alloc('1', NULL, NULL))),

						 Tree_alloc('5', NULL, NULL));

	Tree_print(t);
	printf("\n");

	Tree_free(t);
	return 0;
}