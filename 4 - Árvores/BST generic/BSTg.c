#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "BSTg.h"

BST *BST_alloc(int (*compar)(void *, void *))
{
	BST *bst = NULL;

	if (compar)
	{
		bst = (BST *)malloc(sizeof(BST));
		bst->value = NULL;
		bst->left = NULL;
		bst->right = NULL;
		bst->compar = compar;
	}
	return bst;
}

void BST_free(BST *bst)
{
	if (bst)
	{
		BST_free(bst->left);
		BST_free(bst->right);
		free(bst);
	}
}

void BST_insert(BST *bst, void *value)
{

	if (bst && value)
		if (bst->value == NULL)
			bst->value = value;

		// filho vai para direita.
		else if (bst->compar(bst->value, value) < 0)
		{
			if (bst->right == NULL)
				bst->right = BST_alloc(bst->compar);

			BST_insert(bst->right, value);
		}
		// filho vai para esquerda.
		else if (bst->compar(bst->value, value) > 0)
		{
			if (bst->left == NULL)
				bst->left = BST_alloc(bst->compar);

			BST_insert(bst->left, value);
		}
}

void *BST_search(BST *bst, void *value)
{
	if (bst && value)
		if (bst->value)
			if (bst->compar(bst->value, value) == 0)
				return bst->value;
			else if (bst->compar(bst->value, value) < 0)
				return BST_search(bst->right, value);
			else
				return BST_search(bst->left, value);
	return NULL;
}

void *BST_remove(BST *bst, void *value)
{
	BST *aux = NULL, *n = NULL;

	if (bst && value)
	{
		if (bst->value == value)
		{
			if (bst->left && bst->right)
			{

				n = bst->left;
				while (n->right)
				{
					aux = n;
					n = n->right;
				}

				if (aux)
				{
					aux->right = n->left;
					n->left = bst->left;
				}

				n->right = bst->right;
				free(bst);
				return n;
			}
			else if (bst->left)
			{
				aux = bst->left;
				free(bst);
				return aux;
			}
			else if (bst->right)
			{
				aux = bst->right;
				free(bst);
				return aux;
			}
			else
			{
				free(bst);
				return NULL;
			}
		}
		else if (bst->value < value)
		{
			bst->right = BST_remove(bst->right, value);
		}
		else if (bst->value > value)
		{
			bst->left = BST_remove(bst->left, value);
		}
	}

	return bst;
}

void BST_print(BST *bst, void (*print)(void *))
{
	if (bst)
	{

		// PRE-ORDEM:

		printf("(");
		print(bst->value);
		BST_print(bst->left, print);
		BST_print(bst->right, print);
		printf(") ");
	}
	else
		printf("~"); // sem filho - NULL.
}

void print(void *a)
{
	int *n1 = (int *)a;
	printf("%d ", *n1);
}

int compar(void *a, void *b)
{
	int *n1 = (int *)a;
	int *n2 = (int *)b;
	return *n1 - *n2;
}

/*
int main()
{
	int n[] = {12, 4, 7, 1, 20, 13, 2};
	BST *bst = BST_alloc(compar);

	BST_insert(bst, &n[0]);
	BST_insert(bst, &n[1]);
	BST_insert(bst, &n[2]);
	BST_insert(bst, &n[3]);
	BST_insert(bst, &n[4]);
	BST_insert(bst, &n[5]);
	BST_insert(bst, &n[6]);

	BST_print(bst, print);
	printf("\n");

	bst = BST_remove(bst, &n[4]);
	BST_print(bst, print);
	printf("\n");


	BST_free(bst);
	return 0;
}

*/
