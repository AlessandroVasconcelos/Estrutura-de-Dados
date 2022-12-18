#include <stdlib.h>
#include <stdio.h>
#include "Queue.h"

struct Queue
{
	// tamanho fila alocado
	int size;

	// incio da fila[]
	int begin;

	// fim da fila[]
	int end;

	// tamanho da fila items
	int length;

	// ponteiro para elemento int
	int *items;
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
		q->items = calloc(size, sizeof(Queue));
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

void Queue_push(Queue *q, int item)
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

int Queue_pop(Queue *q)
{
	int aux = 0;
	if (q)
	{
		if (!Queue_isEmpty(q))
		{
			aux = q->items[q->begin];
			q->items[q->begin] = 0;
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

int Queue_begin(Queue *q)
{
	if (q)
	{
		if (!Queue_isEmpty(q))
			return q->items[q->begin];
	}
	return 0;
}

int Queue_end(Queue *q)
{
	if (q)
	{
		if (!Queue_isEmpty(q))
			return q->items[q->end];
	}
	return 0;
}

void Queue_print(Queue *q)
{
	int i;
	if (q)
	{
		printf("Queue(%d): ", q->length);
		if (!Queue_isEmpty(q))
		{
			for (i = q->begin; i != q->end; i = Queue_next(q, i))
				printf("%d ", q->items[i]);

			printf("%d", q->items[i]);
		}
		printf("\n");
	}
}

int Queue_length(Queue *q)
{
	int tam;
	if (q)
		tam = q->length;
	return tam;
}
