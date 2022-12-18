#include <stdlib.h>
#include <stdio.h>
#include "Stack.h"

struct Stack
{
	// tamanho da pilha
	int size;
	// topo da pilha
	int top;
	// ponteiro para elemento generico
	void **elements;
};

Stack *Stack_alloc(int size)
{
	Stack *s = NULL;

	if (size > 0)
	{
		s = malloc(sizeof(Stack)); // aloca dinamicamente uma pilha

		if (s)
		{
			s->size = size;
			s->top = -1;
			s->elements = calloc(size, sizeof(void *));

			if (s->elements == NULL)
			{
				free(s);
				s = NULL;
			}
		}
	}

	return s;
}

void Stack_free(Stack *s)
{
	if (s)
	{
		free(s->elements); // desaloca elementos
		free(s);		   // desaloca stack
	}
}

int Stack_isEmpty(Stack *s)
{
	if (s)
		return s->top == -1; // pilha vazia -1
	return 1;
}

int Stack_isFull(Stack *s)
{
	if (s)
		return s->top == (s->size - 1); // topo == size -1 pilha cheia
	return 0;
}

void Stack_push(Stack *s, void *element)
{
	if (s && !Stack_isFull(s)) // stack != NULL e se a pilha nao esta cheia
	{
		s->top++;					   // inclemento no topo
		s->elements[s->top] = element; // insere elemento no topo nessa posicao
	}
}

void *Stack_pop(Stack *s)
{
	void *el = NULL; // auxiliar
	if (s)
	{
		el = s->elements[s->top];	// auxiliar recebe a posicao no topo
		s->elements[s->top] = NULL; // remove
		s->top--;					// decremento do topo
	}
	return el;
}

void *Stack_top(Stack *s)
{
	if (s)
		return s->elements[s->top];

	return NULL;
}

int Stack_length(Stack *s)
{
	if (s)
		return s->top + 1;

	return 0;
}

void Stack_print(Stack *s, void (*print)(void *))
{
	int i;
	if (s)
	{
		printf("Stack(%d):\n", Stack_length(s));

		for (i = s->top; i >= 0; i--)
		{
			print(s->elements[i]);
			printf("\n");
		}
	}
}
