#include <stdlib.h>
#include <stdio.h>
#include "Deque.h"

Deque *Deque_alloc()
{
	Deque *d = malloc(sizeof(Deque));
	if (d)
	{
		d->length = 0;
		d->front = NULL;
		d->back = NULL;
	}
	return d;
}

void Deque_free(Deque *d)
{
	DequeNode *n, *aux;

	if (d)
	{
		n = d->front;
		while (n)
		{
			aux = n->next;
			free(n);
			n = aux;
		}
		free(d);
	}
}

void Deque_pushFront(Deque *d, void *value)
{
	DequeNode *new = NULL;

	if (d && value)
	{

		new = malloc(sizeof(DequeNode));
		new->value = value;
		new->prev = NULL;
		new->next = NULL;

		if (d->length == 0)
		{
			d->front = new;
			d->back = new;
		}
		else
		{
			d->front->prev = new;
			new->next = d->front;
			d->front = new;
		}

		d->length++;
	}
}

void Deque_pushBack(Deque *d, void *value)
{
	DequeNode *new = NULL;

	if (d && value)
	{

		new = malloc(sizeof(DequeNode));
		new->value = value;
		new->prev = NULL;
		new->next = NULL;

		if (d->length == 0)
		{
			d->front = new;
			d->back = new;
		}
		else
		{
			d->back->next = new;
			new->prev = d->back;
			d->back = new;
		}

		d->length++;
	}
}

void *Deque_popFront(Deque *d)
{
	void *aux = NULL;
	DequeNode *n = NULL;

	if (d)
	{
		aux = d->front->value;

		if (d->length == 1)
		{
			free(d->front);
			d->front = NULL;
			d->back = NULL;
		}
		else
		{
			n = d->front;
			d->front = d->front->next;
			d->front->prev = NULL;
			free(n);
		}
		d->length--;
	}
	return aux;
}

void *Deque_popBack(Deque *d)
{
	void *aux = NULL;
	DequeNode *n = NULL;

	if (d)
	{
		aux = d->front->value;

		if (d->length == 1)
		{
			free(d->front);
			d->front = NULL;
			d->back = NULL;
		}
		else
		{
			n = d->back;
			d->back = d->back->prev;
			d->back->next = NULL;
			free(n);
		}
		d->length--;
	}
	return aux;
}

/*
int main() {
	Deque *d = Deque_alloc();
	int num[] = {1,2,3,4,5,6,7};

	Deque_pushFront(d, &num[0]);
	Deque_pushFront(d, &num[1]);
	Deque_pushFront(d, &num[2]);

	Deque_pushBack(d, &num[3]);
	Deque_pushBack(d, &num[4]);
	Deque_pushBack(d, &num[5]);

	DequeNode *n = d->front;
	int *val;
	while (n) {
		val = (int*) n->value;
		printf("%d ", *val);
		n = n->next;
	}
	printf("\n");

	Deque_popFront(d);
	Deque_popFront(d);
	Deque_popBack(d);
	Deque_popBack(d);

	n = d->front;
	while (n) {
		val = (int*) n->value;
		printf("%d ", *val);
		n = n->next;
	}
	printf("\n");

	Deque_free(d);
}
*/
