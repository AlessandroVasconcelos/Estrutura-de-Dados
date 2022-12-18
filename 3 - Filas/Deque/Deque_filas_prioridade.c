#include <stdio.h>
#include <stdlib.h>
#include "Deque.h"

int main()
{
	int op = 0;
	int cNormal = 1, *ultimaNormal;
	int *sNormal = NULL;

	int cPrioridade = 1, *ultimaPrioridade;
	int *sPrioridade = NULL;

	Deque *qn = Deque_alloc();
	Deque *qp = Deque_alloc();

	do
	{
		printf("1 Atendimento normal\n");
		printf("2 Atendimento prioritário\n");
		printf("3 Mostrar senhas chamadas até o momento\n");
		printf(": ");
		scanf("%d", &op);

		switch (op)
		{
		case 1:
			printf("Senha: %d\n", cNormal);

			sNormal = malloc(sizeof(int));
			*sNormal = cNormal;

			Deque_pushBack(qn, sNormal);

			cNormal++;
			break;
		case 2:
			printf("Senha: %d\n", cPrioridade);

			sPrioridade = malloc(sizeof(int));
			*sPrioridade = cPrioridade;

			Deque_pushBack(qp, sPrioridade);

			cPrioridade++;
			break;
		case 3:
			while (qn->length > 0 || qp->length > 0)
			{
				if (qp->length > 0)
				{

					ultimaPrioridade = Deque_popFront(qp);

					if (qp->length > 0)
						printf("P%d\n", *ultimaPrioridade);
				}

				if (qn->length > 0)
				{

					ultimaNormal = Deque_popFront(qn);

					if (qn->length > 0)
						printf("N%d\n", *ultimaNormal);
				}
			}

			Deque_pushBack(qn, ultimaNormal);
			Deque_pushBack(qp, ultimaPrioridade);

			break;
		default:
			printf("Opção inválida\n");
		}

	} while (op != 3);

	DequeNode *n = qn->front;
	int *val;
	while (n)
	{
		val = (int *)n->value;
		printf("N-%d ", *val);
		n = n->next;
	}
	printf("\n");

	n = qp->front;
	while (n)
	{
		val = (int *)n->value;
		printf("P-%d ", *val);
		n = n->next;
	}
	printf("\n");

	Deque_free(qn);
	Deque_free(qp);
	return 0;
}
