#include <stdlib.h>
#include <stdio.h>
#include "Stack.h"

struct Stack
{
	// tamanho da pilha
	int size;
	// topo da pilha
	int top;
	// ponteiro para elemento int
	int *elements;
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
			s->elements = calloc(size, sizeof(int));

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
}

int Stack_isFull(Stack *s)
{
	if (s)
		return s->top == (s->size - 1); // topo == size -1 pilha cheia
}

void Stack_push(Stack *s, int element)
{
	if (s && !Stack_isFull(s))
	{
		s->top++;					   // inclemento no topo
		s->elements[s->top] = element; // insere elemento no topo nessa posicao
	}
}

int Stack_pop(Stack *s)
{
	int el = 0; // auxiliar
	if (s)
	{
		el = s->elements[s->top]; // auxiliar recebe a posicao no topo
		s->elements[s->top] = 0;  // remove
		s->top--;				  // decremento do topo
	}
	return el;
}

int Stack_top(Stack *s)
{
	if (s)
		return s->elements[s->top];
	return 0;
}

int Stack_length(Stack *s)
{
	if (s)
		return s->top + 1;
	return 0;
}

void Stack_print(Stack *s)
{
	int i;
	if (s)
	{
		printf("Stack(%d):\n", Stack_length(s));

		for (i = s->top; i >= 0; i--)
			printf(" %d\n", s->elements[i]);
	}
}
