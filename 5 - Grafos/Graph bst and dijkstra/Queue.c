#include <stdlib.h>
#include <stdio.h>
#include "Queue.h"

struct Queue
{
	int size;
	int begin;
	int end;
	int length;
	void **items;
};

Queue *Queue_alloc(int size)
{
	Queue *q = malloc(sizeof(Queue));
	if (q)
	{
		q->size = size;
		q->begin = -1;
		q->end = -1;
		q->length = 0;
		q->items = calloc(size, sizeof(void *));
	}
	return q;
}

void Queue_free(Queue *q)
{
	if (q)
	{
		free(q->items);
		free(q);
	}
}

int Queue_isEmpty(Queue *q)
{
	if (q)
	{
		return q->begin == -1 && q->end == -1;
	}
	return 1;
}

int Queue_next(Queue *q, int index)
{
	if (q)
	{
		return (index + 1) % q->size;
	}
	return 0;
}

int Queue_isFull(Queue *q)
{
	if (q)
	{
		if (q->items[Queue_next(q, q->end)] != 0)
			return 1;
	}
	return 0;
}

void Queue_push(Queue *q, void *item)
{
	if (q)
	{
		if (Queue_isEmpty(q))
		{
			q->begin++;
			q->end++;
			q->items[0] = item;
			q->length++;
		}
		else
		{
			if (!Queue_isFull(q))
			{
				q->end = Queue_next(q, q->end);
				q->items[q->end] = item;
				q->length++;
			}
			else
				printf("error: queue is full.\n");
		}
	}
}

void *Queue_pop(Queue *q)
{
	void *aux = NULL;
	if (q)
	{
		if (!Queue_isEmpty(q))
		{
			aux = q->items[q->begin];
			q->items[q->begin] = NULL;
			q->begin = Queue_next(q, q->begin);
			q->length--;

			if (q->length == 0)
			{
				q->begin = -1;
				q->end = -1;
			}
		}
		else
			printf("error: queue is empty.\n");
	}
	return aux;
}

void *Queue_begin(Queue *q)
{
	if (q)
	{
		if (!Queue_isEmpty(q))
			return q->items[q->begin];
	}
	return 0;
}

void *Queue_end(Queue *q)
{
	if (q)
	{
		if (!Queue_isEmpty(q))
			return q->items[q->end];
	}
	return 0;
}

void Queue_print(Queue *q, void (*print)(void *))
{
	int i;
	if (q)
	{
		printf("Queue(%d): ", q->length);
		if (!Queue_isEmpty(q))
		{
			for (i = q->begin; i != q->end; i = Queue_next(q, i))
				print(q->items[i]);

			print(q->items[i]);
		}
		printf("\n");
	}
}

/*
void printInt(void *a) {
	int *num = (int*)a;
	printf("%d ", *num);
}

int main() {
	Queue *q = Queue_alloc(6);
	int n[] = {1,2,3,4,5,6,7}, i;
	for (i=0; i<7; i++)
		Queue_push(q, &n[i]);
	Queue_print(q, printInt);

	printf("removido = ");
	printInt(Queue_pop(q));
	printf("\n");

	Queue_push(q, &n[6]);
	Queue_print(q, printInt);

	printf("inicio = ");
	printInt(Queue_begin(q));
	printf("\n");

	printf("final = ");
	printInt(Queue_end(q));
	printf("\n");

	Queue_print(q, printInt);

	Queue_free(q);
	return 0;
}
*/
