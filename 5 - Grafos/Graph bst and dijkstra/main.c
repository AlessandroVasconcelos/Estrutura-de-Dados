//  gcc main.c Graph.c Heap.c Queue.c -c
//  gcc main.o Graph.o Heap.o Queue.o

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "Graph.h"
#include "Queue.h"
#include "Heap.h"

int *val(int i)
{
	int *v = malloc(sizeof(int));
	*v = i;
	return v;
}

int main()
{
	Graph *g = Graph_alloc();
	int i, n;
	Vertex *v, *path[100];
	Info *inf;

	for (i = 0; i < 14; i++)
		Graph_insertVertex(g, NULL);

	Graph_insertEdge(g, 0, 4, val(8));
	Graph_insertEdge(g, 1, 0, val(6));
	Graph_insertEdge(g, 1, 2, val(5));
	Graph_insertEdge(g, 1, 3, val(2));
	Graph_insertEdge(g, 2, 6, val(2));
	Graph_insertEdge(g, 3, 5, val(2));
	Graph_insertEdge(g, 3, 6, val(3));
	Graph_insertEdge(g, 4, 7, val(3));
	Graph_insertEdge(g, 5, 4, val(5));
	Graph_insertEdge(g, 5, 8, val(2));
	Graph_insertEdge(g, 6, 10, val(4));
	Graph_insertEdge(g, 7, 8, val(1));
	Graph_insertEdge(g, 7, 11, val(5));
	Graph_insertEdge(g, 8, 9, val(4));
	Graph_insertEdge(g, 9, 12, val(9));
	Graph_insertEdge(g, 10, 9, val(2));
	Graph_insertEdge(g, 10, 13, val(2));
	Graph_insertEdge(g, 11, 12, val(6));
	Graph_insertEdge(g, 13, 12, val(3));
	Graph_print(g, NULL);

	Graph_dijkstra(g, 1);

	printf("\nDistancias de 1 para todos os vertices\n");
	printf("Vertice Distancia Anterior\n");
	v = g->first;
	while (v)
	{
		inf = v->value;
		printf("%7d %9d ", v->label, inf->dist);

		if (inf->ant)
			printf("%8d", inf->ant->label);

		printf("\n");
		v = v->next;
	}

	printf("\nCaminho entre 1 e 12\n");
	v = Graph_findByLabel(g, 12);
	n = 0;
	do
	{
		path[n++] = v;
		inf = v->value;
		v = inf->ant;
	} while (v);

	for (i = n - 1; i >= 0; i--)
		printf("(%d)->", path[i]->label);
	printf("\n");

	Graph_free(g);
	return 0;
}

/*
typedef struct {
	char nome[10];
	float nota[3];
} Aluno;

int cmp(void *a, void *b) {
	Aluno *a1 = (Aluno*)a;
	char *nome = (char*)b;
	return strcmp(a1->nome, nome);
}

void print(void *a) {
	Aluno *a1 = (Aluno*)a;
	printf("%s", a1->nome);
}

int main() {
	int i, j;
	Vertex *v, **path;
	Graph *g = Graph_alloc();
	Aluno alunos[5] = {
		{"Adao",{7.0,8.0,9.0}},
		{"Eva",{7.5,10.0,9.0}},
		{"Caim",{5.0,8.0,9.0}},
		{"Abel",{2.0,6.0,4.5}},
		{"Lilith",{8.0,9.0,10.0}}
	};
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
	//Graph_insertEdge(g, 1, 4, NULL);
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

	printf("\nDFS\n");

	for (i=0; i < g->n; i++) {
		path = Graph_dfs(g, alunos[i].nome, cmp);

		if (path) {
			for (j=0; j < g->n; j++) {
				if (path[j] == NULL) {
					break;
				}
				else {
					a = path[j]->value;
					printf("(%s)->", a->nome);
				}
			}
			printf("\n");
		}

		free(path);
	}

	printf("\nBFS\n");

	for (i=0; i < g->n; i++) {
		path = Graph_bfs(g, alunos[i].nome, cmp);

		if (path) {
			for (j=0; j < g->n; j++) {
				if (path[j] == NULL) {
					break;
				}
				else {
					a = path[j]->value;
					printf("(%s)->", a->nome);
				}
			}
			printf("\n");
		}

		free(path);
	}

	Graph_free(g);

	return 0;
}
*/
