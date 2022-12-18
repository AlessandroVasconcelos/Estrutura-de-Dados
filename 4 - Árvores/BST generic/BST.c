#include <stdio.h>
#include <stdlib.h>
#include "BST.h"
#define TEST

BST *BST_alloc(int (*compar)(const void *, const void *))
{
	BST *bst = malloc(sizeof(BST));

	if (bst && compar)
	{
		bst->root = NULL;
		bst->n = 0;
		bst->compar = compar;
		return bst;
	}

	return NULL;
}

void BST_node_free(BST_node *node)
{
	if (node)
	{
		BST_node_free(node->left);
		BST_node_free(node->right);
		free(node);
	}
}

void BST_free(BST *bst)
{
	BST_node *n = NULL;

	if (bst)
	{
		BST_node_free(bst->root);
		free(bst);
	}
}

BST_node *BST_node_alloc(void *item)
{
	BST_node *new = malloc(sizeof(BST_node));
	if (new)
	{
		new->item = item;
		new->left = NULL;
		new->right = NULL;
	}
	return new;
}

void BST_node_insert(BST *bst, BST_node *node, void *item)
{
	BST_node *new = NULL;

	if (bst && node && item)
	{

		if (bst->compar(item, node->item) > 0)
		{
			if (node->right == NULL)
			{
				new = BST_node_alloc(item);
				node->right = new;
			}
			else
			{
				BST_node_insert(bst, node->right, item);
			}
		}
		else if (bst->compar(item, node->item) < 0)
		{
			if (node->left == NULL)
			{
				new = BST_node_alloc(item);
				node->left = new;
			}
			else
			{
				BST_node_insert(bst, node->left, item);
			}
		}
	}
}

void BST_insert(BST *bst, void *item)
{
	if (bst && item)
	{
		if (bst->n)
		{
			BST_node_insert(bst, bst->root, item);
		}
		else
		{
			bst->root = BST_node_alloc(item);
			bst->n++;
		}
	}
}
/*
void *BST_find(BST *bst, void *item) {
	if (bst && item) {
		if (bst->item == item) {
			return bst;
		}
		else if (bst->item > item) {
			return BST_search(bst->left, item);
		}
		else if (bst->item < item) {
			return BST_search(bst->right, item);
		}
	}

	return NULL;
}

BST *BST_remove(BST *bst, int item) {
	BST *aux = NULL, *n = NULL;

	if (bst && item) {
		if (bst->item == item) {
			if (bst->left && bst->right) {

				n = bst->left;
				while (n->right) {
					aux = n;
					n = n->right;
				}

				if (aux) {
					aux->right = n->left;
					n->left = bst->left;
				}

				n->right = bst->right;
				free(bst);
				return n;
			}
			else if (bst->left) {
				aux = bst->left;
				free(bst);
				return aux;
			}
			else if (bst->right) {
				aux = bst->right;
				free(bst);
				return aux;
			}
			else {
				free(bst);
				return NULL;
			}
		}
		else if (bst->item < item) {
			bst->right = BST_remove(bst->right, item);
		}
		else if (bst->item > item) {
			bst->left = BST_remove(bst->left, item);
		}
	}

	return bst;
}
*/

void BST_print(BST_node *bst, void (*print)(void *))
{
	if (bst)
	{
		printf("(");
		print(bst->item);
		BST_print(bst->left, print);
		BST_print(bst->right, print);
		printf(") ");
	}
	else
		printf("~ "); // sem filhos.
}

void print(void *a)
{
	int *n1 = (int *)a;
	printf("%d", *n1);
}

#ifdef TEST

int comp(const void *a, const void *b)
{
	int *n1 = (int *)a;
	int *n2 = (int *)b;
	return *n1 - *n2;
}

/*

int main()
{
	BST *b = BST_alloc(comp);
	int n[] = {4, 2, 1, 3, 7, 5, 6}, i;

	for (i = 0; i < 7; i++)
		BST_insert(b, &n[i]);

	BST_print(b->root, print);
	printf("\n");

	BST_free(b);
	return 0;
}

*/

#endif
