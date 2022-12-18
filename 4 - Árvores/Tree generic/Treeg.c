#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "Treeg.h"


Tree *Tree_alloc(void *value, Tree *left, Tree *right)
{
	Tree *t = NULL;
	if (value)
	{
		t = malloc(sizeof(Tree));
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

void *Tree_getValue(Tree *t)
{
	if (t)
		return t->value;
	else
		return NULL;
}

Tree *Tree_getLeft(Tree *t)
{
	if (t)
		return t->left;
	else
		return NULL;
}

Tree *Tree_getRight(Tree *t)
{
	if (t)
		return t->right;
	else
		return NULL;
}

void Tree_setValue(Tree *t, void *value)
{
	if (t && value)
		t->value = value;
}

void Tree_setLeft(Tree *t, void *value)
{
	if (t && value)
		t->left = Tree_alloc(value, NULL, NULL);
}

void Tree_setRight(Tree *t, void *value)
{
	if (t && value)
		t->right = Tree_alloc(value, NULL, NULL);
}

void Tree_calcular(Tree *t, int *resultado, int *tam, int *left, int *right)
{
	if (t)
	{
		if (t->value)
		{
			Tree_calcular(t->left, resultado, tam, left, right);
			Tree_calcular(t->right, resultado, tam, left, right);
			char *c = (char *)t->value;

			if (*c == '+' || *c == '-' || *c == '*')
			{
				if (isdigit(*(char *)t->left->value))
				{
					*left = atoi((char *)t->left->value);
					t->left->value = left;
				}
				if (isdigit(*(char *)t->right->value))
				{
					*right = atoi((char *)t->right->value);
					t->right->value = right;
				}
				if (*c == '+')
				{
					resultado[*tam] = *(int *)t->left->value + *(int *)t->right->value;
					t->value = &resultado[*tam];
					--*tam;
				}
				else if (*c == '-')
				{
					resultado[*tam] = *(int *)t->left->value - *(int *)t->right->value;
					t->value = &resultado[*tam];
					--*tam;
				}
				else if (*c == '*')
				{
					resultado[*tam] = *(int *)t->left->value * *(int *)t->right->value;
					t->value = &resultado[*tam];
					--*tam;
				}

				free(t->left);
				free(t->right);
				t->left = NULL;
				t->right = NULL;
			}
		}
	}
}

int Tree_alt(Tree *t)
{
	int l, r;
	if (t == NULL)
	{
		return 0;
	}
	else
	{
		l = 1 + Tree_alt(t->left);
		r = 1 + Tree_alt(t->right);

		if (l > r)
			return l;
		else
			return r;
	}
}

/*
void *Tree_getParent(Tree *t, void *value, int (*comparStr)(const void *, const void *))
{
  if (t && value)
  {
	if (t->value)
	{
	  if (comparStr(t->value, value) == 0)
	  {
		printf("Entrou\n");
		return t->parent; // parent = pai
	  }
	  else
	  {
		Tree_getParent(t->left, value, comparStr);
		Tree_getParent(t->right, value, comparStr);
	  }
	}
  }
}
*/

// =======================================================================================================

Tree *Tree_find_main(Tree *t, void *value, int (*compar)(void *, void *), void (*print_char)(void *))
{
	Tree *p = NULL;
	p = Tree_find(t, value, compar);
	if (p == NULL)
	{
		printf("Tree_find retornou NULL\n");
	}
	else
	{
		printf("Valor encontrado: ");
		print_char(p->value);
		printf("\n");
	}
}

Tree *Tree_find(Tree *t, void *value, int (*compar)(void *, void *))
{
	Tree *node = NULL;

	if (t && value && compar)
	{
		if (compar(value, t->value) == 0)
			node = t;
		else
		{
			node = Tree_find(t->left, value, compar);
			if (node == NULL)
				node = Tree_find(t->right, value, compar);
		}
	}
	return node;
}

void Tree_inOrder(Tree *t, void (*process)(void *))
{
	if (t)
	{
		if (t->value)
		{
			Tree_inOrder(t->left, process);
			process(t);
			Tree_inOrder(t->right, process);
		}
	}
}

void Tree_preOrder(Tree *t, void (*process)(void *))
{
	if (t)
	{
		if (t->value)
		{
			process(t);
			Tree_preOrder(t->left, process);
			Tree_preOrder(t->right, process);
		}
	}
}

void Tree_postOrder(Tree *t, void (*process)(void *))
{
	if (t)
	{
		if (t->value)
		{
			Tree_postOrder(t->left, process);
			Tree_postOrder(t->right, process);
			process(t);
		}
	}
}

/*
 3 + 6 * 4 - 1 + 5
		+
	  /   \
	 *     5
	/   \
  +     -
 / \   / \
3   6 4   1

Pre-ordem:
 + * + 3 6 - 4 1 5

In-ordem:
3 + 6 * 4 - 1 + 5

Pos-ordem:
3 6 + 4 1 - * 5 +
*/
/*
void Tree_queue(Tree *t, Queue *q){
	if(t){
		if(t->value){
			Tree_queue(t->left,q);
			Tree_queue(t->right,q);
			Queue_push(q,t->value);
		}
	}
}
*/

void Tree_print_level_main(Tree *bst, void (*print)(void *))
{
	int level = 0;
	if (print)
	{
		Tree_print_level(bst, print, level, '.');
	}
}

void Tree_print_level(Tree *bst, void (*print)(void *), int level, char c)
{
	int i;

	for (i = 0; i < level; i++)
		printf("\t");

	printf("%c/", c);
	if (bst)
	{
		print(bst->value);
		printf("\n");

		Tree_print_level(bst->right, print, level + 1, 'r');
		Tree_print_level(bst->left, print, level + 1, 'l');
	}
	else
		printf("~\n");
}

void Tree_height_main(Tree *t)
{
	int n;
	n = Tree_height(t);
	printf("Altura da arvore: %d\n", n);
}

int Tree_height(Tree *t)
{
	int l, r;
	if (t == NULL)
	{
		return 0;
	}
	else
	{
		l = 1 + Tree_height(t->left);
		r = 1 + Tree_height(t->right);

		if (l > r)
			return l;
		else
			return r;
	}
}

void Tree_eval_main(Tree *t)
{
	int n;
	n = Tree_eval(t);
	printf("Resultado da expressao: %d\n", n);
}

int Tree_eval(Tree *t)
{
	char c;

	if (t)
	{
		c = *((char *)t->value);

		if (c == '+')
		{
			return Tree_eval(t->left) + Tree_eval(t->right);
		}
		else if (c == '*')
		{
			return Tree_eval(t->left) * Tree_eval(t->right);
		}
		else if (c == '-')
		{
			return Tree_eval(t->left) - Tree_eval(t->right);
		}
		else if (c == '/')
		{
			return Tree_eval(t->left) / Tree_eval(t->right);
		}
		else
			return c - 48;
	}
	else
		return 0;
}

void Tree_print_main(Tree *t, void (*print)(void *))
{
	Tree_print(t, print);
	printf("\n");
}

void Tree_print(Tree *t, void (*print)(void *))
{
	if (t)
	{
		if (t->value)
		{
			printf("<");
			print(t->value);
			Tree_print(t->left, print);
			Tree_print(t->right, print);
			printf(">");
		}
	}
	else
		printf("<>");
}

