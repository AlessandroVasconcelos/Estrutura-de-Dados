//  gcc Graph.c main.c -c
//  gcc Graph.o main.o

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "Graph.h"

int cmp(void *a, void *b)
{
	int *n1 = (int *)a;
	int *n2 = (int *)b;
	return *n1 - *n2;
}

void print(void *a)
{
	int *n1 = (int *)a;
	printf("%d ", *n1);
}

int main()
{
	Vertex *v;
	Graph *g = Graph_alloc();
	int num[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	Graph_insertVertex(g, &num[0]);
	Graph_insertVertex(g, &num[1]);
	Graph_insertVertex(g, &num[2]);
	Graph_insertVertex(g, &num[3]);
	Graph_insertVertex(g, &num[4]);

	Graph_insertEdge(g, 0, 1, NULL);
	Graph_insertEdge(g, 0, 3, NULL);
	Graph_insertEdge(g, 1, 3, NULL);
	Graph_insertEdge(g, 1, 2, NULL);
	// Graph_insertEdge(g, 1, 4, NULL);
	Graph_insertEdge(g, 2, 3, NULL);
	Graph_insertEdge(g, 3, 1, NULL);
	Graph_insertEdge(g, 4, 2, NULL);
	Graph_insertEdge(g, 0, 4, NULL);

	Graph_print(g, NULL);

	printf("\n\n");
	Graph_removeVertex(g, 4);
	Graph_print(g, NULL);

	printf("\n\n");
	v = Graph_findByValue(g, &num[3], cmp);
	printf("label = %d, ", v->label);

	Graph_print(g, print);

	Graph_free(g);
	return 0;
}

/*
typedef struct
{
	char nome[10];
	float nota[3];
} Aluno;

int cmp(void *a, void *b)
{
	Aluno *a1 = (Aluno *)a;
	char *nome = (char *)b;
	return strcmp(a1->nome, nome);
}

void print(void *a)
{
	Aluno *a1 = (Aluno *)a;
	printf("%s", a1->nome);
}

int main()
{
	int i, j;
	Vertex *v, **path;
	Graph *g = Graph_alloc();
	Aluno alunos[5] = {
		{"Adao", {7.0, 8.0, 9.0}},
		{"Eva", {7.5, 10.0, 9.0}},
		{"Caim", {5.0, 8.0, 9.0}},
		{"Abel", {2.0, 6.0, 4.5}},
		{"Lilith", {8.0, 9.0, 10.0}}};
	Aluno *a;
	char nome[] = "Eva";

	Graph_insertVertex(g, &alunos[0]);
	Graph_insertVertex(g, &alunos[1]);
	Graph_insertVertex(g, &alunos[2]);
	Graph_insertVertex(g, &alunos[3]);
	Graph_insertVertex(g, &alunos[4]);

	Graph_insertEdge(g, 0, 1, NULL);
	Graph_insertEdge(g, 0, 3, NULL);
	Graph_insertEdge(g, 1, 3, NULL);
	Graph_insertEdge(g, 1, 2, NULL);
	// Graph_insertEdge(g, 1, 4, NULL);
	Graph_insertEdge(g, 2, 3, NULL);
	Graph_insertEdge(g, 4, 2, NULL);
	Graph_insertEdge(g, 0, 4, NULL);

	Graph_print(g, NULL);

	// Graph_removeVertex(g, 4);

	Graph_print(g, NULL);

	v = Graph_findByValue(g, nome, cmp);
	printf("label = %d, ", v->label);
	a = v->value;
	printf("%s %.1f %.1f %.1f\n", a->nome, a->nota[0], a->nota[1], a->nota[2]);

	Graph_print(g, print);

	Graph_free(g);
	return 0;
}
*/