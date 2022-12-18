#include <stdio.h>
#include <stdlib.h>
#include "Heap.h"

Heap *Heap_alloc(int max, int (*compar)(const void *, const void *))
{
	Heap *h = NULL;

	if (compar && max > 0)
	{
		h = malloc(sizeof(Heap));
		h->n = 0;
		h->max = max;
		h->itens = calloc(max, sizeof(Heap));
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

void Heap_fixDown(Heap *h, int i)
{
	int j, f;
	void *aux;

	// indice do pai
	j = i;

	// enquanto nao ultrapassar o tamanho do vetor
	while (2 * j + 1 < h->n)
	{

		// seleciona filho da esquerda
		f = 2 * j + 1;

		// se existe filho da direita E (esquerda) < (direita)
		if (f < h->n - 2 && h->compar(h->itens[f], h->itens[f + 1]) < 0)
		{
			// seleciona filho da direita
			f++;
		}

		// se (pai) >= (filho selecionado)
		if (h->compar(h->itens[j], h->itens[f]) >= 0)
		{
			break;
		}
		else
		{
			// troca (pai) <-> (filho selecionado)
			aux = h->itens[j];
			h->itens[j] = h->itens[f];
			h->itens[f] = aux;

			// novo indice do pai
			j = f;
		}
	}
}

void Heap_fixUp(Heap *h, int m)
{
	int i = m;
	void *aux;

	while (i >= 0 && h->compar(h->itens[(i - 1) / 2], h->itens[i]) < 0)
	{
		aux = h->itens[(i - 1) / 2];
		h->itens[(i - 1) / 2] = h->itens[i];
		h->itens[i] = aux;
		i = (i - 1) / 2;
	}
}

void *Heap_remove(Heap *h)
{
	void *value = NULL;
	if (h)
	{
		if (h->n > 0)
		{
			value = h->itens[0];
			h->itens[0] = h->itens[h->n - 1];
			h->n--;
			Heap_fixDown(h, 0);
		}
	}
	return value;
}

void Heap_insert(Heap *h, void *value)
{
	if (h && value)
	{
		h->itens[h->n] = value;
		h->n++;
		Heap_fixUp(h, h->n - 1);
	}
}

void Heap_changeValue(Heap *h, int m, void *value)
{
	int i = m;
	if (h && value)
	{
		if (i < h->n && i >= 0)
		{
			if (h->compar(value, h->itens[i]) > 0)
			{
				h->itens[i] = value;
				Heap_fixUp(h, i);
			}
			else if (h->compar(value, h->itens[i]) < 0)
			{
				h->itens[i] = value;
				Heap_fixDown(h, i);
			}
		}
	}
}

Heap *Heap_build(void *arr, int length, int max, int (*compar)(const void *, const void *))
{
	Heap *h = Heap_alloc(max, compar);
	char *c;
	int i;

	if (h)
	{
		c = (char *)arr;

		for (i = 0; i < length; i++)
		{
			h->itens[i] = c;
			c = c + max;
		}

		h->n = length;

		for (i = (length - 1) / 2; i >= 0; i--)
		{
			Heap_fixDown(h, i);
		}
	}

	return h;
}