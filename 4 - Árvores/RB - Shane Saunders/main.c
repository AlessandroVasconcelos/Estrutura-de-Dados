//  gcc main.c RB.c -c
//  gcc main.o RB.o

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "RB.h"

int comparStr(const void *a, const void *b)
{
	char *s1 = (char *)a;
	char *s2 = (char *)b;
	return strcmp(s1, s2);
}

void printTreeStr(RB_node *tree)
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

// main de string
int main()
{
	char *str[] = {"Jan", "Fev", "Mar", "Abr", "Mai", "Jun", "Jul"};

	RB *treeStr = RB_alloc(comparStr);

	RB_insert(treeStr, str[2]);
	RB_insert(treeStr, str[0]);
	RB_insert(treeStr, str[5]);
	RB_insert(treeStr, str[1]);
	RB_insert(treeStr, str[6]);
	RB_insert(treeStr, str[3]);
	RB_insert(treeStr, str[4]);

	printTreeStr(treeStr->root);
	printf("\n");

	char *s = "Jul";
	RB_delete(treeStr, s); // apaga umes de Julho.

	printTreeStr(treeStr->root);
	printf("\n");

	RB_free(treeStr);
	return 0;
}

/*

int comparInt(const void *a, const void *b)
{
	int *n1 = (int *)a;
	int *n2 = (int *)b;
	return *n1 - *n2;
}

void printTreeInt(RB_node *tree)
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

	RB *treeInt = RB_alloc(comparInt);

	RB_insert(treeInt, &num[0]);
	RB_insert(treeInt, &num[1]);
	RB_insert(treeInt, &num[2]);
	RB_insert(treeInt, &num[3]);
	RB_insert(treeInt, &num[4]);
	RB_insert(treeInt, &num[5]);
	RB_insert(treeInt, &num[6]);

	printTreeInt(treeInt->root);
	printf("\n");

	int n = 5;
	RB_delete(treeInt, &n); // apaga o numero 5.
	//RB_delete(treeInt, &num[5]); // apaga o numero 5.

	printTreeInt(treeInt->root);
	printf("\n");

	RB_free(treeInt);
	return 0;
}



/*

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

void printTreeCar(RB_node *tree)
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

// main struct
int main()
{
	RB *treeCar = RB_alloc(comparCar);
	Car c[] = { {"207"   , "Peugeot"},
				{"Gol"   , "Volkswagen"},
				{"HB20"  , "Hyundai"},
				{ "Focus", "Ford"},
				{"QQ"    , "Chery"}};

	RB_insert(treeCar,&c[0]);
	RB_insert(treeCar,&c[1]);
	RB_insert(treeCar,&c[2]);
	RB_insert(treeCar,&c[3]);
	RB_insert(treeCar,&c[4]);

	printTreeCar(treeCar->root);
	printf("\n");

	Car car = {"HB20",NULL}; // soh e necessario o nome para comparar
	RB_delete(treeCar,&car);
	printTreeCar(treeCar->root);
	printf("\n");

	RB_delete_min(treeCar);
	printTreeCar(treeCar->root);
	printf("\n");

	RB_free(treeCar);
	return 0;
}

*/
