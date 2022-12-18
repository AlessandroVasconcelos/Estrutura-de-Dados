//  gcc main.c BST.c -c
//  gcc main.o BST.o

#include <stdio.h>
#include <stdlib.h>
#include "BST.h"

BST *BST_min(BST *bst)
{
	BST *n = NULL;

	if (bst)
	{

		if (bst->left)
		{
			n = bst->left;
			while (n->left)
			{
				n = n->left;
			}
		}
		else
			return bst;
	}

	return n;
}

int BST_isIn(BST *bst, int value)
{

	while (bst)
	{
		if (bst->value == value)
			return 1;

		if (value > bst->value)
			bst = bst->right;
		else
			bst = bst->left;
	}

	return 0;
}

void BST_vecToBST(BST *bst, int vec[], int begin, int end)
{
	int center = (begin + end) / 2;
	BST_insert(bst, vec[center]);

	if (begin != center)
		BST_vecToBST(bst, vec, begin, center - 1);

	if (end != center)
		BST_vecToBST(bst, vec, center + 1, end);
}

int main()
{
	BST *b = BST_alloc(), *busca, *min;
	BST_insert(b, 1);
	BST_insert(b, 7);
	BST_insert(b, 3);
	BST_insert(b, 6);
	BST_insert(b, 2);
	BST_print(b);
	printf("\n");

	busca = BST_search(b, 6);
	printf("%p %d\n", busca, busca->value);

	busca = BST_search(b, 8);
	printf("%p\n", busca);

	min = BST_min(b);
	printf("%p %d\n", min, min->value);

	printf("%s\n", BST_isIn(b, 7) ? "Sim" : "Nao");
	printf("%s\n", BST_isIn(b, 11) ? "Sim" : "Nao");

	//         0 1 2 3 4 5 6
	int n[] = {1, 2, 3, 4, 5, 6, 7};
	BST *c = BST_alloc();

	BST_vecToBST(c, n, 0, 6);
	BST_print(c);
	printf("\n");

	c = BST_remove(c, 3);
	BST_print(c);
	printf("\n");

	c = BST_remove(c, 4);
	BST_print(c);
	printf("\n");

	BST_free(b);
	BST_free(c);
	return 0;
}
