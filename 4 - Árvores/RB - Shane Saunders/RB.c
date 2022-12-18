/*** File RB.c - Red-Black Tree ***/
/*
 *   Shane Saunders
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "RB.h"

/* Protótipos para funções apenas visíveis dentro deste arquivo. */
RB_node *RB_restructure(RB *t, int tos, RB_node *x, RB_node *y, RB_node *z);
RB_node *RB_restructure2(RB *t, int tos, RB_node *x, RB_node *y, RB_node *z);

RB *RB_alloc(int (*compar)(const void *, const void *))
{
	RB *t;

	t = malloc(sizeof(RB));
	t->root = NULL;
	t->compar = compar;
	t->stack = malloc(RB_STACK_SIZE * sizeof(RB_node *));
	t->n = 0;

	return t;
}

/* RB_free() - Libera espaço usado pela árvore rubro-negra apontada por t. */
void RB_free(RB *t)
{
	RB_node *p, **stack;
	int tos;

	/* Para liberar todos os nós da árvore, uma primeira busca em profundidade é realizada isso é implementado usando uma pilha. */
	if (t->root)
	{
		stack = t->stack;
		stack[0] = t->root;
		tos = 1;
		while (tos)
		{
			p = stack[--tos];
			if (p->left)
			{
				stack[tos++] = p->left;
			}
			if (p->right)
			{
				stack[tos++] = p->right;
			}
			free(p);
		}
		free(stack);
	}

	free(t);
}

void *RB_insert(RB *t, void *item)
{
	RB_node *x, *p, *q, *m, **attach_x;
	int (*compar)(const void *, const void *);
	int cmp_result;
	RB_colour col;
	RB_node **stack;
	int tos;

	tos = 0;
	if ((p = t->root))
	{
		compar = t->compar;
		stack = t->stack;

		/* Explorar repetidamente o ramo esquerdo ou o ramo direito
		 * dependendo do valor da key, até que um branch vazio seja escolhido.
		 */
		for (;;)
		{
			stack[tos++] = p;
			cmp_result = compar(item, p->item);
			if (cmp_result < 0)
			{
				p = p->left;
				if (!p)
				{
					p = stack[--tos];
					attach_x = &p->left;
					break;
				}
			}
			else if (cmp_result > 0)
			{
				p = p->right;
				if (!p)
				{
					p = stack[--tos];
					attach_x = &p->right;
					break;
				}
			}
			else
			{
				return p->item;
			}
		}
		col = Red;
	}
	else
	{
		attach_x = &t->root;
		col = Black;
	}

	x = malloc(sizeof(RB_node));
	x->left = x->right = NULL;
	x->item = item;
	x->colour = col;

	*attach_x = x;
	t->n++;

	/* A reestruturação ou recoloração será necessária se o nó x e seu pai, p, forem ambos vermelhos.
	 */
	if (tos > 0)
		while (p->colour == Red)
		{ /* Problema vermelho duplo. */

			/* Obtenha um ponteiro para o pai de p, m, e o irmão, q.*/
			m = stack[--tos];
			q = p == m->left ? m->right : m->left;

			/* Determine se é necessário reestruturar ou recolorir. */
			if (!q || q->colour == Black)
			{
				/* O irmão é preto. ==> Realize a reestruturação. */

				/* Reestruture de acordo com a ordem da esquerda para a direita, dos nós m, p e x.
				 */
				m = RB_restructure(t, tos, m, p, x);
				m->colour = Black;
				m->left->colour = m->right->colour = Red;

				/* A reestruturação elimina o problema do duplo vermelho. */
				break;
			}
			/* else */

			/* Irmão também é vermelho. ==> Realize a recoloração. */
			p->colour = Black;
			q->colour = Black;

			if (tos == 0)
				break; /* O nó raiz sempre permanece preto. */

			m->colour = Red;

			/* Continue, verificando a coloração mais acima. */
			x = m;
			p = stack[--tos];
		}

	return NULL;
}

void *RB_find(RB *t, void *key_item)
{
	RB_node *p, *next_p;
	int (*compar)(const void *, const void *);
	int cmp_result;

	compar = t->compar;

	if ((next_p = t->root))
	{
		/* Explore repetidamente o ramo esquerdo ou direito, dependendo do
		 * valor da key, até que o item correto seja encontrado.
		 */
		do
		{
			p = next_p;
			cmp_result = compar(key_item, p->item);
			if (cmp_result < 0)
			{
				next_p = p->left;
			}
			else if (cmp_result > 0)
			{
				next_p = p->right;
			}
			else
			{
				/* Item encontrado. */
				return p->item;
			}
		} while (next_p);
	}

	return NULL;
}

void *RB_find_min(RB *t)
{
	RB_node *p, *next_p;

	if ((next_p = t->root))
	{
		/* Para localizar o mínimo, os ramos esquerdos são escolhidos repetidamente até não podermos explorar mais.*/
		do
		{
			p = next_p;
			next_p = p->left;
		} while (next_p);
	}
	else
	{
		return NULL;
	}

	return p->item;
}

void *RB_delete(RB *t, void *key_item)
{
	RB_node *p, *r, *x, *y, *z, *b, *new_y;
	RB_node *m;
	RB_colour remove_col;
	void *return_item;
	int (*compar)(const void *, const void *);
	int cmp_result;
	RB_node **stack;
	int i, tos;

	/* Tente localizar o item a ser excluído. */
	if ((p = t->root))
	{
		compar = t->compar;
		stack = t->stack;
		tos = 0;

		for (;;)
		{
			stack[tos++] = p;
			cmp_result = compar(key_item, p->item);
			if (cmp_result < 0)
			{
				p = p->left;
			}
			else if (cmp_result > 0)
			{
				p = p->right;
			}
			else
			{
				/* Item encontrado. */
				break;
			}
			if (!p)
				return NULL;
		}
	}
	else
	{
		return NULL;
	}

	/* p aponta para o nó a ser excluído e está atualmente no topo da pilha.
	 */
	if (!p->left)
	{
		tos--; /* Ajuste tos para remover p.*/
		/* O filho direito substitui p.*/
		if (tos == 0)
		{
			r = t->root = p->right;
			x = y = NULL;
		}
		else
		{
			x = stack[--tos];
			if (p == x->left)
			{
				r = x->left = p->right;
				y = x->right;
			}
			else
			{
				r = x->right = p->right;
				y = x->left;
			}
		}
		remove_col = p->colour;
	}
	else if (!p->right)
	{
		tos--; /* Ajuste tos para remover p.*/
		/* O filho esquerdo substitui p. */
		if (tos == 0)
		{
			r = t->root = p->left;
			x = y = NULL;
		}
		else
		{
			x = stack[--tos];
			if (p == x->left)
			{
				r = x->left = p->left;
				y = x->right;
			}
			else
			{
				r = x->right = p->left;
				y = x->left;
			}
		}
		remove_col = p->colour;
	}
	else
	{
		/*Salve a posição da pilha de p. */
		i = tos - 1;

		/* Filho mínimo, m, na subárvore direita substitui p. */
		m = p->right;
		do
		{
			stack[tos++] = m;
			m = m->left;
		} while (m);
		m = stack[--tos];

		/* Atualize os ponteiros filho esquerdo ou direito do pai de p.*/
		if (i == 0)
		{
			t->root = m;
		}
		else
		{
			x = stack[i - 1]; /* pai de p. */
			if (p == x->left)
			{
				x->left = m;
			}
			else
			{
				x->right = m;
			}
		}

		/* Atualize a parte da árvore da qual m foi removida e atribua m ao filho
		 * ponteiros de p (somente se m não for o filho à direita de p).
		 */
		stack[i] = m; /* O nó m substitui o nó p na pilha. */
		x = stack[--tos];
		r = m->right;
		if (tos != i)
		{ /*x é igual ao pai de m. */
			y = x->right;
			x->left = r;
			m->right = p->right;
		}
		else
		{ /* m era o filho à direita de p, e x é igual a m. */
			y = p->left;
		}
		m->left = p->left;

		/* Tratamos o nó m como o nó que foi removido. */
		remove_col = m->colour;
		m->colour = p->colour;
	}

	/* Obtenha o valor de retorno e libere o espaço usado pelo nó p.*/
	return_item = p->item;
	free(p);

	t->n--;

	/* Os ponteiros x, y e r apontam para nós que podem estar envolvidos em reestruturação e recoloração.
	 * x - o pai do nó removido.
	 * y - o irmão do nó removido.
	 * r - o nó que substituiu o nó removido.
	 * Do código acima, a próxima entrada da pilha será o pai de nó x.
	 */

	/* O número de nós pretos nos caminhos para todos os nós externos (ponteiros filhos NULL)
	 * devem permanecer os mesmos para todos os caminhos.
	 * Reestruturação ou a recoloração dos nós pode ser necessária para impor isso.
	 */
	if (remove_col == Black)
	{
		/* A remoção de um nó preto requer algum ajuste. */

		if (!r || r->colour == Black)
		{
			/* Um nó preto substituiu o nó preto excluído.
			 * Observe que nós externos (ponteiros filhos NULL)
			 * são sempre pretos, então se r for NULL, será tratado como um nó preto.
			 */

			/* Isso causa um problema de preto duplo, já que o nó r precisaria
			 * ser colorido em preto duplo para que a cor preta
			 * caminhos através de r para permanecer o mesmo que para outros caminhos.
			 */

			/* Se r for o nó raiz, a cor preta dupla não é necessária para manter o equilíbrio de cores.
			 * Caso contrário, algum ajuste de os nós próximos são necessários para eliminar o preto duplo problema.
			 * NOTA: x aponta para o pai de r.
			 */
			if (x)
				for (;;)
				{

					/* Existem três casos de ajuste:
					 * 1. O irmão de r, y, é preto e tem um filho vermelho, z.
					 * 2. O irmão de r, y, é negro e tem dois filhos negros.
					 * 3. O irmão de r, y, é vermelho.
					 */
					if (y->colour == Black)
					{

						/* Observe a avaliação condicional para atribuir z. */
						if (((z = y->left) && z->colour == Red) ||
							((z = y->right) && z->colour == Red))
						{
							/* Caso 1: faça uma reestruturação dos nós x, y e z. */

							b = RB_restructure(t, tos, x, y, z);
							b->colour = x->colour;
							b->left->colour = b->right->colour = Black;

							break;
						}
						else
						{
							/* Caso 2: recolorir nó y vermelho. */

							y->colour = Red;

							if (x->colour == Red)
							{
								x->colour = Black;
								break;
							}
							/* else */

							if (tos == 0)
								break; /* Nível de raiz atingido. */
									   /* else */

							r = x;
							x = stack[--tos]; /* x <- pai de x. */
							y = x->left == r ? x->right : x->left;
						}
					}
					else
					{
						/* Caso 3: Reestrutura os nós x, yez, onde:
						 * - Se o nó y é o filho esquerdo de x, então z é o filho esquerdo filho de y
						 * Caso contrário, z é o filho à direita de y.
						 */
						if (x->left == y)
						{
							new_y = y->right;
							z = y->left;
						}
						else
						{
							new_y = y->left;
							z = y->right;
						}

						RB_restructure(t, tos, x, y, z);
						y->colour = Black;
						x->colour = Red;

						/* Como x desceu um lugar na árvore, e y é o
						 * novo o pai de x, a pilha deve ser ajustada para que
						 * o pai de x é identificado corretamente na próxima chamada para RB_restructure().
						 */
						stack[tos++] = y;

						/* Após a reestruturação, o nó r tem um irmão preto, new_y,
						 * então tanto o caso 1 quanto o caso 2 se aplicam.
						 * Se o caso 2 se aplica o problema do duplo preto não reaparece.
						 */
						y = new_y;

						/* Observe a avaliação condicional para atribuir z. */
						if (((z = y->left) && z->colour == Red) ||
							((z = y->right) && z->colour == Red))
						{
							/* Caso 1: faça uma reestruturação dos nós x, y e z. */

							b = RB_restructure(t, tos, x, y, z);
							b->colour = Red; /* Como o nó x era vermelho.*/
							b->left->colour = b->right->colour = Black;
						}
						else
						{
							/* Caso 2: recolorir nó y vermelho. */

							/* Observe que o nó y é preto e o nó x é vermelho. */

							y->colour = Red;
							x->colour = Black;
						}

						break;
					}
				}
		}
		else
		{
			/* Um nó vermelho substituiu o nó preto excluído. */

			/* Neste caso, podemos simplesmente colorir o nó vermelho de preto.*/
			r->colour = Black;
		}
	}

	return return_item;
}

void *RB_delete_min(RB *t)
{
	RB_node *p, *r, *x, *y, *z, *b, *new_y;
	RB_colour remove_col;
	void *return_item;
	RB_node **stack;
	int tos;

	/* Tente localizar o item a ser excluído.*/
	if ((p = t->root))
	{
		stack = t->stack;
		tos = 0;

		/* Para localizar o mínimo, os ramos esquerdos são escolhidos repetidamente até que não possamos explorar mais. */
		do
		{
			stack[tos++] = p;
			p = p->left;
		} while (p);
		p = stack[--tos]; /* Nó a ser excluído. */
	}
	else
	{
		return NULL;
	}

	/* O filho direito substitui p. */
	if (tos == 0)
	{
		r = t->root = p->right;
		x = y = NULL;
	}
	else
	{
		x = stack[--tos];
		r = x->left = p->right;
		y = x->right;
	}
	remove_col = p->colour;

	/* Obtenha o valor de retorno e o espaço livre usado pelo nó p. */
	return_item = p->item;
	free(p);

	t->n--;

	/* Os ponteiros x, y e r apontam para nós que podem estar envolvidos em reestruturação e recoloração.
	 * x - o pai do nó removido.
	 * y - o irmão do nó removido.
	 * r - o nó que substituiu o nó removido.
	 */

	/* O número de nós pretos nos caminhos para todos os nós externos (NULL filho
	 * ponteiros) devem permanecer os mesmos para todos os caminhos.
	 * Reestruturação ou a recoloração dos nós pode ser necessária para impor isso.
	 */
	if (remove_col == Black)
	{
		/* A remoção de um nó preto requer algum ajuste. */

		if (!r || r->colour == Black)
		{
			/* Um nó preto substituiu o nó preto excluído. Observe que
			 * nós externos (ponteiros filhos NULL) são sempre pretos, então
			 * se r for NULL, será tratado como um nó preto.
			 */

			/* Isso causa um problema de preto duplo, já que o nó r precisaria
			 * ser colorido em preto duplo para que a cor preta
			 * caminhos através de r para permanecer o mesmo que para outros caminhos.
			 */

			/* Se r for o nó raiz, a cor preta dupla não é necessária para manter o equilíbrio de cores.
			 * Caso contrário, algum ajuste de os nós próximos são necessários para eliminar o preto duplo problema.
			 * NOTA: x aponta para o pai de r.
			 */
			if (x)
				for (;;)
				{

					/* Existem três casos de ajuste:
					 *  1.  o irmão de r, y, é negro e tem um filho vermelho, z.
					 *  2.  o irmão de r, y, é negro e tem dois filhos negros.
					 *  3.  o irmão de r, y, é vermelho.
					 */
					if (y->colour == Black)
					{

						/* Observe a avaliação condicional para atribuir z. */
						if (((z = y->left) && z->colour == Red) ||
							((z = y->right) && z->colour == Red))
						{
							/* Caso 1: faça uma reestruturação dos nós x, y e z. */

							b = RB_restructure2(t, tos, x, y, z);
							b->colour = x->colour;
							b->left->colour = b->right->colour = Black;

							break;
						}
						else
						{
							/* Caso 2: recolorir nó y vermelho. */

							y->colour = Red;

							if (x->colour == Red)
							{
								x->colour = Black;
								break;
							}
							/* else */

							if (tos == 0)
								break; /* Nível raiz atingido. */
									   /* else */

							r = x;
							x = stack[--tos]; /* x <- pai de x. */
							y = x->left == r ? x->right : x->left;
						}
					}
					else
					{
						/* Caso 3: Reestrutura os nós x, yez, onde:
						 * - Se o nó y é o filho esquerdo de x, então z é o filho esquerdo
						 * filho de y. Caso contrário, z é o filho à direita de y.
						 */
						if (x->left == y)
						{
							new_y = y->right;
							z = y->left;
						}
						else
						{
							new_y = y->left;
							z = y->right;
						}

						RB_restructure2(t, tos, x, y, z);
						y->colour = Black;
						x->colour = Red;

						/* Como x desceu um lugar na árvore, e y é o
						 * novo o pai de x, a pilha deve ser ajustada para que
						 * o pai de x é identificado corretamente na próxima chamada
						 * para RB_restructure().
						 */
						stack[tos++] = y;

						/* Após a reestruturação, o nó r tem um irmão preto, new_y,
						 * então tanto o caso 1 quanto o caso 2 se aplicam. Se o caso 2 se aplica o problema do duplo preto não reaparece.
						 * Nota: x ainda aponta para o pai de r, mas y deve ser atualizado para apontar para o novo irmão de r, new_y.
						 */
						y = new_y;

						/* Observe a avaliação condicional para atribuir z. */
						if (((z = y->left) && z->colour == Red) ||
							((z = y->right) && z->colour == Red))
						{
							/* Caso 1: faça uma reestruturação dos nós x, y e z.
							 */

							b = RB_restructure2(t, tos, x, y, z);
							b->colour = Red; /* Como o nó x era vermelho. */
							b->left->colour = b->right->colour = Black;
						}
						else
						{
							/* Caso 2: recolorir nó y vermelho.*/

							/* Observe que o nó y é preto e o nó x é vermelho. */
							y->colour = Red;
							x->colour = Black;
						}

						break;
					}
				}
		}
		else
		{
			/* Um nó vermelho substituiu o nó preto excluído.*/

			/* Neste caso, podemos simplesmente colorir o nó vermelho de preto.*/
			r->colour = Black;
		}
	}

	return return_item;
}

/*** Funções de reestruturação. ***/

/* RB_restructure() - Função de reestruturação geral - verifica todos os casos de reestruturação.
 */
RB_node *RB_restructure(RB *t, int tos, RB_node *x,
						RB_node *y, RB_node *z)
{
	RB_node *parent, *mid_node;

	if (y == x->left)
	{
		if (z == y->left)
		{ /* em ordem: z, y, x */
			mid_node = y;
			y->left = z;
			x->left = y->right;
			y->right = x;
		}
		else
		{ /* em ordem: y, z, x */
			mid_node = z;
			y->right = z->left;
			z->left = y;
			x->left = z->right;
			z->right = x;
		}
	}
	else
	{
		if (z == y->left)
		{ /* em ordem: x, z, y */
			mid_node = z;
			x->right = z->left;
			z->left = x;
			y->left = z->right;
			z->right = y;
		}
		else
		{ /* em ordem: x, y, z */
			mid_node = y;
			x->right = y->left;
			y->left = x;
			y->right = z;
		}
	}

	if (tos != 0)
	{
		parent = t->stack[tos - 1];
		if (x == parent->left)
		{
			parent->left = mid_node;
		}
		else
		{
			parent->right = mid_node;
		}
	}
	else
	{
		t->root = mid_node;
	}

	return mid_node;
}

/* RB_restructure2() - Função de reestruturação usada por delete_min.
 * Lá são menos casos de reestruturação a serem considerados, pois se sabe que y sempre ser o filho certo de x.
 */
RB_node *RB_restructure2(RB *t, int tos, RB_node *x,
						 RB_node *y, RB_node *z)
{
	RB_node *parent, *mid_node;

	if (z == y->left)
	{ /* em ordem:  x, z, y */
		mid_node = z;
		x->right = z->left;
		z->left = x;
		y->left = z->right;
		z->right = y;
	}
	else
	{ /* em ordem::  x, y, z */
		mid_node = y;
		x->right = y->left;
		y->left = x;
		y->right = z;
	}

	if (tos != 0)
	{
		parent = t->stack[tos - 1];
		if (x == parent->left)
		{
			parent->left = mid_node;
		}
		else
		{
			parent->right = mid_node;
		}
	}
	else
	{
		t->root = mid_node;
	}

	return mid_node;
}