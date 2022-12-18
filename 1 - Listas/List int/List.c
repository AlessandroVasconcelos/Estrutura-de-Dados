#include <stdlib.h>
#include <stdio.h>
#include "List.h"

typedef struct Node Node;

struct Node
{
	int value;
	// proximo no
	Node *next;
};

struct List
{
	int length;
	// tamanho da lista
	Node *first;
	// ultimo no
	Node *last;
};

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

void List_insert(List *l, int value)
{
	Node *new = NULL;
	if (l)
	{
		new = malloc(sizeof(Node));
		new->value = value;
		new->next = NULL;

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

void List_remove(List *l, int value)
{
	Node *n, *ant = NULL;
	if (l)
	{
		n = l->first;

		while (n)
		{
			if (n->value == value)
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

void List_print(List *l)
{
	Node *n;
	if (l)
	{
		n = l->first;

		while (n)
		{
			printf("%d ", n->value);
			n = n->next;
		}
		printf("\n");
	}
}

void List_insertSorted(List *l, int value)
{
	Node *new = NULL, *n, *ant = NULL;
	if (l)
	{
		new = malloc(sizeof(Node));
		new->value = value;
		new->next = NULL;

		n = l->first;
		while (n)
		{
			if (value <= n->value)
			{
				if (ant == NULL)
				{
					new->next = l->first;
					l->first = new;
				}
				else
				{
					new->next = n;
					ant->next = new;
				}
				break;
			}
			ant = n;
			n = n->next;
		}

		if (l->length == 0)
			l->first = new;
		else
			ant->next = new;

		l->length++;
	}
}

List *List_qsort(List *l)
{
	List *a = NULL, *b = NULL;
	Node *n = NULL, *pivot = NULL;

	if (l)
	{

		if (l->length < 2)
		{
			return l;
		}
		else
		{
			a = List_alloc();
			b = List_alloc();
			pivot = l->first;

			n = pivot->next;
			while (n)
			{
				if (n->value < pivot->value)
					List_insert(a, n->value);
				else
					List_insert(b, n->value);

				n = n->next;
			}

			a = List_qsort(a);
			b = List_qsort(b);

			List_insert(a, pivot->value);

			n = b->first;
			while (n)
			{
				List_insert(a, n->value);
				n = n->next;
			}

			List_free(b);
			List_free(l);

			return a;
		}
	}
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

int invert(Node *head, Node *tail, Node *aux)
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

int List_invert(List *l)
{
	Node *aux;
	Node *new_first = l->last;
	if (l)
	{
		invert(NULL, l->first, aux);
		l->first = aux;
		l->first = new_first;
		int *i = (int *)l;
		return *i;
	}
	return 0;
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

int List_removeMax(List *l)
{
	// atual = primeiro
	Node *cur = l->first;
	// anterior = NULL
	Node *prev = NULL;

	int max = 0;
	int count = 0;

	// enquanto atual != NULL
	while (cur)
	{
		// se atual > max
		if (cur->value > max)
		{
			// max = atual
			max = cur->value;
		}
		// atual = atual->next
		cur = cur->next;
	}

	// atual = primeiro
	cur = l->first;

	// enquanto atual != NULL
	while (cur)
	{
		// se atual == max
		if (cur->value == max)
		{
			// se anterior == NULL
			if (prev == NULL)
			{
				// primeiro = atual->next
				l->first = cur->next;
				free(cur);
				// atual = primeiro
				cur = l->first;
			}
			else
			{
				// anterior->next = atual->next
				prev->next = cur->next;
				free(cur);
				// atual = anterior->next
				cur = prev->next;
			}
		}
		else
		{
			// anterior = atual
			prev = cur;
			// atual = atual->next
			cur = cur->next;
		}
	}
	return max;
}
