#include <stdlib.h>
#include <stdio.h>
#include "Tree.h"

Tree *Tree_alloc(int value, Tree *left, Tree *right)
{
	Tree *t = malloc(sizeof(Tree));
	if (t)
	{
		t->value = value;
		t->left = left;
		t->right = right;
	}
	return t;
}

void Tree_free(Tree *t)
{
	if (t)
	{
		Tree_free(t->left);
		t->left = NULL;
		Tree_free(t->right);
		t->right = NULL;
		free(t);
	}
}

void Tree_print(Tree *t)
{
	/*
   if (t)
	{
		Tree_print(t->left);
		printf("<%c ",t->value);
		Tree_print(t->right);
		printf("> ");
   }
   else
   {
		printf("<> ");
   }
   */
	if (t)
	{

		// Em ordem:

		Tree_print(t->left);
		printf("%c ", t->value);
		Tree_print(t->right);

		/*
		// Pre-ordem:
		printf("%c ",t->value);
		Tree_print(t->left);
		Tree_print(t->right);

		// Pos-ordem:

		Tree_print(t->left);
		Tree_print(t->right);
		printf("%c ",t->value);
		*/
	}
}
