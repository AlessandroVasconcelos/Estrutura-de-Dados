#include <stdlib.h>
#include <stdio.h>
#include "Heap.h"

Heap *Heap_alloc(int max, int (*compar)(void *, void *))
{
	Heap *h = NULL;
	if (max > 0 && compar)
	{
		h = malloc(sizeof(Heap));
		h->n = 0;
		h->max = max;
		h->itens = calloc(max, sizeof(void *));
		h->compar = compar;
	}
	return h;
}

void Heap_free(Heap *h)
{
	if (h)
	{
		free(h->itens);
		free(h);
	}
}

void swap(Heap *h, int i, int j)
{
	void *aux = NULL;
	if (h)
	{
		if (i >= 0 && i < h->n &&
			j >= 0 && j < h->n)
		{

			aux = h->itens[i];
			h->itens[i] = h->itens[j];
			h->itens[j] = aux;
		}
	}
}

void fixDown(Heap *h, int i)
{
	int j, f;
	if (h && i >= 0)
	{
		j = i;
		while (2 * j + 1 < h->n)
		{
			f = 2 * j + 1;

			if (f < h->n - 2 &&
				h->compar(h->itens[f], h->itens[f + 1]) < 0)
			{
				f++;
			}

			if (h->compar(h->itens[j], h->itens[f]) >= 0)
			{
				break;
			}
			else
			{
				swap(h, j, f);
				j = f;
			}
		}
	}
}

void fixUp(Heap *h, int m)
{
	int i;
	if (h && m >= 0 && m < h->n)
	{
		i = m;
		while (i >= 0 &&
			   h->compar(h->itens[(i - 1) / 2], h->itens[i]) < 0)
		{
			swap(h, (i - 1) / 2, i);
			i = (i - 1) / 2;
		}
	}
}

void Heap_insert(Heap *h, void *item)
{
	if (h && item)
	{
		if (h->n < h->max)
		{
			h->itens[h->n++] = item;
			fixUp(h, h->n - 1);
		}
		else
			printf("error: heap is full\n");
	}
}

void *Heap_remove(Heap *h)
{
	void *item = NULL;

	if (h)
	{
		item = h->itens[0];
		h->itens[0] = h->itens[h->n - 1];
		h->n--;
		fixDown(h, 0);
	}

	return item;
}

void Heap_increase(Heap *h, int i, void *item)
{
	if (h && item)
	{
		h->itens[i] = item;
		fixUp(h, i);
	}
}

void Heap_decrease(Heap *h, int i, void *item)
{
	if (h && item)
	{
		h->itens[i] = item;
		fixDown(h, i);
	}
}

void heapsort(Heap *h)
{
}
