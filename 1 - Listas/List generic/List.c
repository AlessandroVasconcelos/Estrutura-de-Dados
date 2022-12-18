#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "List.h"

// lista encadeada simples

typedef struct Node Node;

struct Node
{
	void *value;
	// proximo no
	Node *next;
};

struct List
{
	// tamanho da lista
	int length;
	// primeiro no
	Node *first;
	// ultimo no
	Node *last;
};

typedef struct
{
	int num;
	int exp;
} termo;

List *List_alloc()
{
	List *l = malloc(sizeof(List));
	if (l)
	{
		l->length = 0;
		l->first = NULL; // primeiro aponta para NULL
	}
	return l;
}

void List_free(List *l)
{
	Node *n, *aux;
	if (l)
	{
		n = l->first;
		while (n)
		{
			aux = n->next;
			free(n);
			n = aux;
		}
		free(l);
	}
}

void List_insert(List *l, void *value)
{
	Node *new = NULL;
	if (l)
	{
		new = malloc(sizeof(Node));
		new->value = value;

		if (l->length == 0) /* insere novo nó no início da lista */
		{
			l->first = new;
			l->last = new;
		}
		else
		{
			l->last->next = new;
			l->last = new;
		}

		l->length++;
	}
}

void List_print(List *l, void (*print)(void *))
{
	Node *n;
	if (l && print)
	{
		if (l->length > 0)
		{
			n = l->first;
			while (n)
			{
				print(n->value);
				n = n->next;
			}
			printf("\n");
		}
		else
		{
			printf("(empty list)\n");
		}
	}
}

/*
void List_print(List *l, void (*print)(void*))
{
	Node *n = l->first;

	while (n != NULL)
	{
		print(n->value);
		n = n->next;
	}
		printf("\n");
}*/

void *List_find(List *l, void *value, int (*compar)(void *, void *))
{
	Node *n;
	if (l && value && compar)
	{
		n = l->first;
		while (n)
		{
			if (compar(n->value, value) == 0)
			{
				printf("\nO elemento esta na lista...");
				return n->value;
			}
			n = n->next;
		}
	}
	printf("\nO elemento nao esta na lista...");
	return NULL;
}

void *List_remove(List *l, void *value, int (*compar)(void *, void *))
{
	Node *n, *ant = NULL, *v;
	if (l && value && compar)
	{
		n = l->first;

		while (n)
		{
			if (compar(n->value, value) == 0)
			{

				if (ant == NULL)
					l->first = n->next;
				else
				{
					if (n->next == NULL)
						l->last = ant;
					ant->next = n->next;
				}
				v = n->value;
				free(n);
				l->length--;
				return v;
			}
			n = n->next;
		}
	}
	return NULL;
}

void *List_remove1(List *l, void *value, int (*compar)(void *, void *))
{
	Node *n, *ant = NULL;
	if (l && value && compar)
	{
		n = l->first;

		while (n)
		{
			if (compar(n->value, value) == 0)
			{
				if (ant == NULL)
					l->first = n->next;
				else
					ant->next = n->next;
				free(n);
				l->length--;
				break;
			}
			ant = n;
			n = n->next;
		}
	}
}

int List_getLenght(List *l)
{
	if (l)
		return l->length;
	else
		return 0;
}

//+++++++++++++++++++++_MAIS_FUNCOES_ATRIBUIDAS_++++++++++++++++++++++++++++

void List_insertBegin(List *l, void *value)
{
	Node *new = NULL;

	if (l && value)
	{
		new = malloc(sizeof(Node));
		new->value = value;
		new->next = NULL;

		if (l->length > 0)
			new->next = l->first;

		l->first = new;
		l->length++;
	}
}

void List_insertEnd(List *l, void *value)
{
	Node *cur = NULL;
	Node *new = NULL;

	if (l && value)
	{
		new = malloc(sizeof(Node));
		new->value = value;
		new->next = NULL;

		if (l->length > 0)
		{
			cur = l->first;

			while (cur->next)
				cur = cur->next;

			cur->next = new;
		}
		else
			l->first = new;

		l->length++;
	}
}

void *List_removeBegin(List *l)
{
	Node *rem = NULL;

	if (l)
	{
		if (l->length > 0)
		{
			rem = l->first;
			l->first = l->first->next;
			rem->next = NULL;
		}

		l->length--;
	}

	return rem;
}

void *List_removeEnd(List *l)
{
	Node *rem = NULL;
	Node *cur = NULL;

	if (l)
	{
		if (l->length > 0)
		{
			if (l->length == 1)
			{
				rem = l->first;
				l->first = NULL;
			}
			else
			{
				cur = l->first;

				while (cur->next->next)
					cur = cur->next;

				rem = cur->next;
				cur->next = NULL;
			}

			l->length--;
		}
	}

	return rem;
}

void *List_findAndRemove(List *l, void *value, int (*compar)(void *, void *))
{
	Node *cur = NULL;
	Node *prv = NULL;

	if (l && value && compar)
	{
		if (l->length > 0)
		{

			cur = l->first;

			while (cur)
			{
				if (compar(cur->value, value) == 0)
				{
					if (prv == NULL)
						l->first = cur->next;
					else
						prv->next = cur->next;

					cur->next = NULL;
					l->length--;
					return cur->value;
				}

				prv = cur;
				cur = cur->next;
			}
		}
	}

	return cur;
}

void *List_removeMaior(List *l, int (*compar)(void *, void *))
{
	Node *ma = NULL;
	void *aux = NULL;
	int i, c = 0;

	if (l && compar)
	{
		if (l->length > 0)
		{
			ma = l->first;
			aux = ma->value;
			while (ma)
			{
				if (compar(ma->value, aux) == 1)
					aux = ma->value;
				ma = ma->next;
			}
		}
	}

	if (l && compar)
	{
		if (l->length > 0)
		{
			ma = l->first;
			while (ma)
			{
				if (compar(ma->value, aux) == 0)
					c++;
				ma = ma->next;
			}
		}
	}

	for (i = 0; i < c; i++)
		List_findAndRemove(l, aux, compar);

	return aux;
}

int count(Node *n, int i)
{
	if (n)
	{
		i++;
		return 1 + count(n->next, 1);
	}
	else
		return 0;
}

int List_count(List *l)
{
	int i = 0;
	if (l)
	{
		i = count(l->first, i);
	}
	return i;
}

void invert(Node *head, Node *tail, Node *aux)
{
	if (tail) // recursive case
	{
		invert(tail, tail->next, aux);
		tail->next = head;
	}
	else
	{
		aux = head; // base case
	}
}

List *List_invert(List *l)
{
	Node *aux;
	Node *new_first = l->last;

	invert(NULL, l->first, aux);
	l->first = aux;
	l->first = new_first;
	return l;
}

List *List_concat(List *l1, List *l2)
{
	Node *cur = l1->first;

	while (cur->next)
	{
		cur = cur->next;
	}
	cur->next = l2->first;

	l1->length = l1->length + l2->length;
	l2->length = 0;
	l2->first = NULL;
}

void List_insertSorted(List *l, void *value, int (*compar)(void *, void *));
List *List_qsort(List *l, int (*compar)(void *, void *));
