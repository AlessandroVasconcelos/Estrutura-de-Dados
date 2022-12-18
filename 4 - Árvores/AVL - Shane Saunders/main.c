//  gcc main.c AVL.c -c
//  gcc main.o AVL.o

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "AVL.h"

typedef struct car
{
	char *nome;
	char *brand;

} Car;

int comparCar(const void *a, const void *b)
{
	Car *c1 = (Car *)a;
	Car *c2 = (Car *)b;
	return strcmp(c1->nome, c2->nome);
}

void printTreeCar(AVL_node *tree)
{
	Car *c;
	if (tree)
	{
		c = (Car *)tree->item;

		// Em ordem:

		printTreeCar(tree->left);
		printf("\n(%s, %s)", c->nome, c->brand);
		printTreeCar(tree->right);
	}
}

void print(void *a)
{
	int *n1 = (int *)a;
	printf("%d", *n1);
}

// main struct
int main()
{
	AVL *treeCar = AVL_alloc(comparCar);
	Car c[] = {{"207", "Peugeot"},
			   {"Gol", "Volkswagen"},
			   {"HB20", "Hyundai"},
			   {"Focus", "Ford"},
			   {"QQ", "Chery"}};

	AVL_insert(treeCar, &c[0]);
	AVL_insert(treeCar, &c[1]);
	AVL_insert(treeCar, &c[2]);
	AVL_insert(treeCar, &c[3]);
	AVL_insert(treeCar, &c[4]);

	printTreeCar(treeCar->root);
	printf("\n");

	Car car = {"HB20", NULL}; // soh e necessario o nome para comparar
	AVL_delete(treeCar, &car);
	printTreeCar(treeCar->root);
	printf("\n");

	AVL_delete_min(treeCar);
	printTreeCar(treeCar->root);
	printf("\n");

	AVL_free(treeCar);
	return 0;
}

/*

// main de string


int comparStr(const void *a, const void *b)
{
	char *s1 = (char *)a;
	char *s2 = (char *)b;
	return strcmp(s1, s2);
}

void printTreeStr(AVL_node *tree)
{
	char *s;
	if (tree)
	{
		s = (char *)tree->item;

		// Em ordem:

		printTreeStr(tree->left);
		printf("%s ", s);
		printTreeStr(tree->right);
	}
}

int main()
{
	char *str[] = {"Jan", "Fev", "Mar", "Abr", "Mai", "Jun", "Jul"};

	AVL *treeStr = AVL_alloc(comparStr);

	AVL_insert(treeStr, str[2]);
	AVL_insert(treeStr, str[0]);
	AVL_insert(treeStr, str[5]);
	AVL_insert(treeStr, str[1]);
	AVL_insert(treeStr, str[6]);
	AVL_insert(treeStr, str[3]);
	AVL_insert(treeStr, str[4]);

	printTreeStr(treeStr->root);
	printf("\n");

	char *s = "Jul";
	AVL_delete(treeStr, s); // apaga umes de Julho.

	printTreeStr(treeStr->root);
	printf("\n");

	AVL_free(treeStr);
	return 0;
}
*/

/*

int comparInt(const void *a, const void *b)
{
	int *n1 = (int *)a;
	int *n2 = (int *)b;
	return *n1 - *n2;
}

void printTreeInt(AVL_node *tree)
{
	int *n;
	if (tree)
	{
		n = (int *)tree->item;

		// Em ordem:

		printTreeInt(tree->left);
		printf("%d ", *n);
		printTreeInt(tree->right);
	}
}

// main de inteiros
int main()
{
	int num[] = {0,1,2,3,4,5,6,7,8,9,10,11,12};

	AVL *treeInt = AVL_alloc(comparInt);

	AVL_insert(treeInt, &num[0]);
	AVL_insert(treeInt, &num[1]);
	AVL_insert(treeInt, &num[2]);
	AVL_insert(treeInt, &num[3]);
	AVL_insert(treeInt, &num[4]);
	AVL_insert(treeInt, &num[5]);
	AVL_insert(treeInt, &num[6]);

	printTreeInt(treeInt->root);
	printf("\n");

	int n = 5;
	AVL_delete(treeInt, &n); // apaga o numero 5.
	//AVL_delete(treeInt, &num[5]); // apaga o numero 5.

	printTreeInt(treeInt->root);
	printf("\n");

	AVL_free(treeInt);
	return 0;
}

*/

/*
 */
