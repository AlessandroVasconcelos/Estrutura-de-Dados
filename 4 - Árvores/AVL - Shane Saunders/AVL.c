/*** File AVL.c - AVL Tree ***/
/*
 *   Shane Saunders
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "AVL.h"

/* Implementação de teste que usa o histórico de pilhas para substituir o uso dos ponteiros para o próximo e anterior. */

AVL *AVL_alloc(int (*compar)(const void *, const void *))
{
	AVL *t;

	t = malloc(sizeof(AVL));
	t->root = NULL;
	t->compar = compar;
	t->stack = malloc(AVL_STACK_SIZE * sizeof(AVL_node *));
	t->path_info = malloc(AVL_STACK_SIZE * sizeof(signed char));
	t->n = 0;

	return t;
}

/* AVL_free() - Libera o espaço usado pela árvore AVL apontado por t.*/
void AVL_free(AVL *t)
{
	int tos;
	AVL_node *p, **stack;

	/* Para liberar todos os nós na árvore, uma primeira pesquisa de profundidade é realizada
	 * Isso é implementado usando uma pilha.
	 */
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
	}

	free(t->stack);
	free(t->path_info);
	free(t);
}

void *AVL_insert(AVL *t, void *item)
{
	int (*compar)(const void *, const void *);
	int cmp_result;
	void *return_result;
	AVL_node *x, *p, *q, *r, **attach_x;
	AVL_node **stack;
	int tos, stack_n;
	signed char *path_info;

	compar = t->compar;

	/* A pilha armazena informações sobre o caminho para um nó.Para a matriz
	 * Stack, pilha [i] segura os (i) os nós no caminho da raiz, com
	 * O nó 0º é o nó raiz.Para o Array Path_info [],
	 * path_info [i] é -1 ou 1, dependendo se o ramo esquerdo ou direito
	 * O ramo foi atravessado do (i) o nó.A matriz Path_info pode então
	 * ser usado para atualizar informações de balanceamento.
	 */
	stack = t->stack;
	path_info = t->path_info;
	tos = 0;

	/* Procure a posição de inserção, começando no nó raiz, se isso
	 * existe.
	 */
	if ((p = t->root))
	{
		/* Explorar repetidamente o ramo esquerdo ou o ramo direito
		 * dependendo do valor da key, até uma posição de ramificação vazia seja encontrado.
		 */
		for (;;)
		{
			stack[tos] = p;
			cmp_result = compar(item, p->item);
			if (cmp_result < 0)
			{
				path_info[tos] = -1;
				tos++;
				p = p->left;
				if (!p)
				{
					attach_x = &stack[tos - 1]->left;
					break;
				}
			}
			else if (cmp_result > 0)
			{
				path_info[tos] = 1;
				tos++;
				p = p->right;
				if (!p)
				{
					attach_x = &stack[tos - 1]->right;
					break;
				}
			}
			else
			{
				return p->item;
			}
		}
	}
	else
	{
		attach_x = &t->root;
	}

	/* NULL será devolvido, indicando que não havia item com a mesma key na árvore.
	 */
	return_result = NULL;

	/* Espaço alocado para o novo nó.*/
	x = malloc(sizeof(AVL_node));
	x->left = x->right = NULL;
	x->balance = 0;
	x->item = item;

	/* attach_x é um ponteiro para a variável de ponteiro para adicionar o nó à árvore.
	 */
	*attach_x = x;
	t->n++;

	/* Agora atravesse a pilha, atualizando informações de balanceamento dos anteriores e realizando rotação, se necessário.
	 */
	stack_n = tos;
	while (tos)
	{
		p = stack[--tos];
		if (p->balance == 0)
		{
			/* Alterações de balanceamento de 0 a 1 ou -1.O comprimento do
			 * O caminho mais longo de p para uma folha aumentou em 1, então
			 * Continue a iteração para os pais da p.
			 */
			p->balance += path_info[tos];
		}
		else
		{
			p->balance += path_info[tos];
			if (p->balance == 0)
			{
				/* O balanceamento mudou de -1 ou 1 para 0.
				 * o comprimento do caminho mais longo de p para uma folha não mudou, Então pare a iteração.
				 */
				break; /* A árvore é balanceada.*/
			}
			else
			{
				/* balanceamento alterações de 1 para 2 ou de -1 para -2.
				 * Agora a árvore está desbalanceada e a rotação deve ser realizada.
				 *
				 * Para esta descrição, defina a direção x como o
				 * direção do excesso de balanceamento e direção y, como o
				 * outra direção.Para esta descrição, é mais simples
				 * Consulte o filho X e o filho Y, desde que o uso foi
				 * e à direita depende do balanceamento da árvore.
				 */

				/* O tipo de rotação que ocorre depende se
				 * o balanceamento do filho de P (do qual P foi alcançado), q,
				 * está na mesma direção que o balanceamento da p.
				 * Isso é determinado olhando para PATH_INFO [TOS].
				 */
				q = stack[tos + 1];
				if (path_info[tos] == path_info[tos + 1])
				{
					/* Existe a seguinte estrutura de árvore:
					 *  A - x árvore filho de q.
					 *  B - y árvore filho de q.
					 *  C - y filho de p.
					 */

					/* Para a rotação:
					 *  - A árvore B substitui o nó q como o filho de p.
					 *  - nó p substitui a árvore b como o filho de q.
					 */
					if (path_info[tos] == 1)
					{
						p->right = q->left;
						q->left = p;
					}
					else
					{
						p->left = q->right;
						q->right = p;
					}

					p->balance = q->balance = 0;

					/* Um ponteiro filho do pai de p muda de p para q.
					 * Se p era a raiz, o nó raiz muda.
					 */
					if (tos != 0)
					{
						if (path_info[tos - 1] == 1)
						{
							stack[tos - 1]->right = q;
						}
						else
						{
							stack[tos - 1]->left = q;
						}
					}
					else
					{
						t->root = q;
					}

					break;
				}
				else
				{
					if (tos + 2 != stack_n)
					{
						r = stack[tos + 2];
					}
					else
					{
						r = x; /* Caso especial: R é o nó inserido. */
					}
					/* Existe a seguinte estrutura de árvore:
					 *  A - x árvore filho de q.
					 *  B - x árvore filho de r.
					 *  C - y árvore filho de r.
					 *  D - y árvore filho de p.
					 */

					/* Para a rotação:
					 *  - A árvore B substitui o nó r como o filho de q.
					 *  - A árvore C substitui o nó q como o filho de p.
					 *  - Nó q substitui a árvore B como o filho de r.
					 *  - Nó p substitui a árvore c como o filho de r.
					 */
					if (path_info[tos] == 1)
					{
						q->left = r->right;
						p->right = r->left;
						r->right = q;
						r->left = p;
						if (r->balance == 1)
						{
							p->balance = -1;
							q->balance = 0;
						}
						else if (r->balance == -1)
						{
							p->balance = 0;
							q->balance = 1;
						}
						else
						{
							p->balance = q->balance = 0;
						}
					}
					else
					{
						q->right = r->left;
						p->left = r->right;
						r->left = q;
						r->right = p;
						if (r->balance == 1)
						{
							p->balance = 0;
							q->balance = -1;
						}
						else if (r->balance == -1)
						{
							p->balance = 1;
							q->balance = 0;
						}
						else
						{
							p->balance = q->balance = 0;
						}
					}
					r->balance = 0;

					/* Um ponteiro filho do pai de p muda de p para r.
					 * Se p era a raiz, o nó raiz muda.
					 */
					if (tos != 0)
					{
						if (path_info[tos - 1] == 1)
						{
							stack[tos - 1]->right = r;
						}
						else
						{
							stack[tos - 1]->left = r;
						}
					}
					else
					{
						t->root = r;
					}
					break;
				}
			}
		}
	}

	return return_result;
}

void *AVL_find(AVL *t, void *key_item)
{
	int (*compar)(const void *, const void *);
	int cmp_result;
	AVL_node *p, *next_p;

	if ((next_p = t->root))
	{
		compar = t->compar;

		/* Explora repetidamente o ramo esquerdo ou direito, dependendo do
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

void *AVL_find_min(AVL *t)
{
	AVL_node *p, *next_p;

	if ((next_p = t->root))
	{
		/* Para localizar o mínimo, os galhos esquerdos são escolhidos repetidamente até não podemos explorar mais.
		 */
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

void *AVL_delete(AVL *t, void *key_item)
{
	void *return_item;
	int (*compar)(const void *, const void *);
	int cmp_result;
	AVL_node *p, *prev_p;
	AVL_node *m, *prev_m;
	AVL_node *q, *r;
	AVL_node **stack;
	int tos, stack_p;
	signed char *path_info;

	/* Se a árvore estiver vazia de retorna NULL. */
	if (!(p = t->root))
		return NULL;

	compar = t->compar;

	/* A pilha armazena informações sobre o caminho para um nó.Para a matriz
	 * pilha, pilha [i] segura os (i) os nós no caminho da raiz, com
	 * o nó 0º é o nó raiz.Para o Array Path_info [],
	 * path_info [i] é -1 ou 1, dependendo se o ramo esquerdo ou direito
	 * O ramo foi atravessado do (i) o nó.A matriz Path_info [] pode
	 * Em seguida, seja usado para atualizar informações de balanceamento.
	 */
	stack = t->stack;
	path_info = t->path_info;
	tos = 0;

	/* Tente localizar o item a ser excluído. */
	for (;;)
	{
		cmp_result = compar(key_item, p->item);
		if (cmp_result < 0)
		{
			path_info[tos] = -1;
			stack[tos++] = p;
			p = p->left;
		}
		else if (cmp_result > 0)
		{
			path_info[tos] = 1;
			stack[tos++] = p;
			p = p->right;
		}
		else
		{
			/* Item encontrado. */
			break;
		}
		if (!p)
		{
			/* Item não encontrado. */
			return NULL;
		}
	}

	/* P aponta para o nó a ser excluído.Atualmente, o prev_p está na parte superior da pilha.
	 */
	if (!p->left)
	{
		/* filho direito substitui p. */
		if (tos == 0)
		{
			t->root = p->right;
		}
		else
		{
			prev_p = stack[tos - 1];
			if (p == prev_p->left)
			{
				prev_p->left = p->right;
			}
			else
			{
				prev_p->right = p->right;
			}
		}
	}
	else if (!p->right)
	{
		/* O filho esquerdo substitui p. */
		if (tos == 0)
		{
			t->root = p->left;
		}
		else
		{
			prev_p = stack[tos - 1];
			if (p == prev_p->left)
			{
				prev_p->left = p->left;
			}
			else
			{
				prev_p->right = p->left;
			}
		}
	}
	else
	{
		/* Filho mínimo, m, na subárvore direita substitui p. */
		path_info[tos] = 1;
		stack[tos] = p;
		stack_p = tos++; /* Salve a posição da pilha de p. */

		m = p->right; /* Garantido para não ser NULL. */
		do
		{
			path_info[tos] = -1;
			stack[tos++] = m;
			m = m->left;
		} while (m);
		m = stack[--tos];

		/* Atualize os ponteiros filho esquerdo ou direito de prev_p. */
		if (stack_p == 0)
		{
			t->root = m;
		}
		else
		{
			prev_p = stack[stack_p - 1];
			if (p == prev_p->left)
			{
				prev_p->left = m;
			}
			else
			{
				prev_p->right = m;
			}
		}

		/* Atualize a árvore da qual a parte m foi removida e atribua m os ponteiros filhos de p
		 * (somente se m não for o filho de p certo).
		 */
		prev_m = stack[tos - 1];
		if (prev_m != p)
		{
			prev_m->left = m->right;
			m->right = p->right;
		}
		m->left = p->left;

		/* Dê o nó m o nó de balanceamento P e substitua a entrada da pilha para P por m.*/
		m->balance = p->balance;
		stack[stack_p] = m;
	}

	/* Obtenha valor de retorno e espaço livre usado pelo nó p. */
	return_item = p->item;
	free(p);
	t->n--;

	/* Realize rotações, se necessário, para reequilibrar a árvore.Isso está feito
	 * percorrendo a pilha, atualizando informações de balanceamento dos anteriores e realizando rotações, se necessário.
	 *
	 * O ponteiro P agora aponta para o nó que está sendo considerado para rebalanceamento.
	 */
	while (tos)
	{
		p = stack[--tos];
		if (p->balance == 0)
		{
			/* Alterações de balanceamento de 0 a 1 ou -1.O comprimento de apenas um
			 * O caminho de p para uma folha diminuiu em 1, de modo que o comprimento do caminho mais longo é inalterado
			 * Portanto, a iteração pode parar.
			 */
			p->balance -= path_info[tos];
			break; /* A árvore é balanceada. */
		}
		else
		{
			p->balance -= path_info[tos];

			/* Observe que se o balanceamento mudou de -1 ou 1 para 0, o comprimento de
			 * O caminho mais longo de P para uma folha deve ter diminuído.
			 * Portanto, as iterações para atualizações de balanceamento continuarão.
			 */

			if (p->balance != 0)
			{
				/* O balanceamento muda de 1 para 2 ou de -1 para -2.
				 * Agora a árvore está desbalanceada e a rotação deve ser
				 * realizado.
				 *
				 * Para esta descrição, defina a direção x como o
				 * direção do excesso de balanceamento e direção y, conforme o
				 *outra direção. Para esta descrição é mais simples
				 * referem-se ao filho x e ao filho y, pois o uso deixou
				 * e certo depende do balanceamento da árvore.
				 */

				/* O tipo de rotação que ocorre depende se
				 * o balanceamento do outro filho de p (não o filho de onde p foi alcançado)
				 * está na mesma direção que o balanceamento de p.
				 */
				if (path_info[tos] == 1)
				{
					q = p->left; /* o outro filho de p. */
				}
				else
				{
					q = p->right; /* p's other child. */
				}
				if (path_info[tos] != q->balance)
				{
					/* O balanceamento (P, Q) será:
					 * (2,1), (2,0), (-2,-1), or (-2,0)
					 */

					/* Existe a seguinte estrutura de árvore:
					 *  A - x árvore filho de q.
					 *  B - y árvore filho de q.
					 *  C - y filho de p.  (A exclusão ocorreu na árvore C.)
					 */

					/* Para a rotação:
					 *  - A árvore B substitui o nó q como o filho de p.
					 *  - nó p substitui a árvore b como o filho de q.
					 */
					if (path_info[tos] != 1)
					{
						p->right = q->left;
						q->left = p;
					}
					else
					{
						p->left = q->right;
						q->right = p;
					}

					/* Um ponteiro filho do pai de p muda de p para q.
					 * Se p era a raiz, o nó raiz muda.
					 */
					if (tos != 0)
					{
						if (path_info[tos - 1] == 1)
						{
							stack[tos - 1]->right = q;
						}
						else
						{
							stack[tos - 1]->left = q;
						}
					}
					else
					{
						t->root = q;
					}

					/* Atualiza as informações do balanceamento dos nós P e Q.*/
					if (q->balance == 0)
					{
						p->balance = p->balance > 0 ? 1 : -1;
						q->balance = -p->balance;
						break; /* A árvore é balanceada. */
					}
					else
					{
						p->balance = q->balance = 0;
					}

					/* A menos que q->balance == 0, as iterações continuarão, pois
					 * o comprimento do caminho mais longo diminuiu.
					 */
				}
				else
				{
					/*O balanceamento de (p, q) será:
					 * (2,-1) or (-2,1)
					 */

					/* Existe a seguinte estrutura de árvore:
					 *  A - x árvore filho de q.
					 *  B - x árvore filho de r.
					 *  C - y árvore filho de r.
					 *  D - y árvore filho de p.  (A exclusão ocorreu na árvore d)
					 */

					/* Para a rotação:
					 *  - A árvore B substitui o nó r como o filho de q.
					 *  - A árvore C substitui o nó q como o filho de p.
					 *  - Nó q substitui a árvore B como o filho de r.
					 *  - Nó p substitui a árvore c como o filho de r.
					 */
					if (path_info[tos] != 1)
					{
						r = q->left;
						q->left = r->right;
						p->right = r->left;
						r->right = q;
						r->left = p;
						if (r->balance == 1)
						{
							p->balance = -1;
							q->balance = 0;
						}
						else if (r->balance == -1)
						{
							p->balance = 0;
							q->balance = 1;
						}
						else
						{
							p->balance = q->balance = 0;
						}
					}
					else
					{
						r = q->right;
						q->right = r->left;
						p->left = r->right;
						r->left = q;
						r->right = p;
						if (r->balance == 1)
						{
							p->balance = 0;
							q->balance = -1;
						}
						else if (r->balance == -1)
						{
							p->balance = 1;
							q->balance = 0;
						}
						else
						{
							p->balance = q->balance = 0;
						}
					}
					r->balance = 0;

					/* Um ponteiro filho do pai de p muda de p para r.
					 * Se p era a raiz, o nó raiz muda.
					 */
					if (tos != 0)
					{
						if (path_info[tos - 1] == 1)
						{
							stack[tos - 1]->right = r;
						}
						else
						{
							stack[tos - 1]->left = r;
						}
					}
					else
					{
						t->root = r;
					}

					/* Continue com outras iterações, já que o comprimento do caminho mais longo diminuiu.
					 */
				}
			}
		}
	}

	return return_item;
}

void *AVL_delete_min(AVL *t)
{
	void *return_item;
	AVL_node *p;
	AVL_node *q, *r;
	AVL_node **stack;
	int tos;

	/* A pilha armazena informações sobre o caminho para um nó. Para a matriz
	 * stack, stack[i] contém os (i)th nós no caminho da raiz, com
	 * o 0º nó sendo o nó raiz. Para a matriz path_info[],
	 * path_info[i] é -1 ou 1 dependendo se o branch esquerdo ou direito
	 * o ramo foi percorrido a partir do (i)º nó. A matriz path_info[] pode
	 * então ser usado para atualizar as informações de balanceamento.
	 */
	stack = t->stack;
	tos = 0;

	/* Tente localizar o item a ser excluído. */
	if ((p = t->root))
	{
		/* Para localizar o mínimo, os ramos esquerdos são escolhidos repetidamente até não podemos explorar mais.
		 */
		do
		{
			stack[tos++] = p;
			p = p->left;
		} while (p);
		p = stack[--tos];
	}
	else
	{
		return NULL;
	}

	/* filho direito de p substitui p. */
	if (tos == 0)
	{
		t->root = p->right;
	}
	else
	{
		stack[tos - 1]->left = p->right;
		/* Stack [TOS-1] aponta para os pais da p. */
	}

	/* Obtenha o valor de retorno e o espaço livre usado pelo nó p. */
	return_item = p->item;
	free(p);
	t->n--;

	/* Realiza rotações, se necessário, para reequilibrar a árvore. Isso está feito
	 * percorrendo a pilha, atualizando informações de balanceamento de ancestrais,
	 * e realizando rotações se necessário.
	 *
	 * O ponteiro p agora aponta para o nó que está sendo considerado para rebalanceamento.
	 */
	while (tos)
	{
		p = stack[--tos];
		if (p->balance == 0)
		{
			/* O balanceamento muda de 0 para 1. O comprimento de apenas um
			 * caminho de p para uma folha diminuiu em 1, então o comprimento do
			 * o caminho mais longo permanece inalterado. Portanto, a iteração pode parar.
			 */
			p->balance++;
			;
			break; /* A árvore é balanceada.*/
		}
		else
		{
			p->balance++;

			/* Observe que se balance mudou de -1 para 0, o comprimento do caminho mais longo de p até uma folha deve ter diminuído.
			 * Portanto, as iterações para atualizações de balanceamento continuarão.
			 */

			if (p->balance != 0)
			{
				/* O balanceamento muda de 1 para 2.
				 * Agora a árvore está desbalanceada, e a rotação deve ser realizada.
				 */

				/* O tipo de rotação que ocorre depende se
				 * o balanceamento do outro filho de p (não o filho de onde p foi alcançado)
				 * está na mesma direção que o balanceamento de p.
				 */
				q = p->right; /* P é o outro filho. */
				if (q->balance != -1)
				{
					/* O balanceamento (p, q) será também:
					 * (2,1), or (2,0)
					 */

					/* Existe a seguinte estrutura em árvore:
					 * A - árvore direita  filho de q.
					 * B - árvore esquerda filho de q.
					 * C - árvore esquerda filho de p.
					 * (Exclusão ocorreu na árvore C.)
					 */

					/* Para a rotação:
					 * - a árvore B substitui o nó q como filho de p à direita.
					 * - o nó p substitui a árvore B como o filho de q esquerdo.
					 */
					p->right = q->left;
					q->left = p;

					/* Um ponteiro filho do pai de p muda de p para q.
					 * Se p era a raiz, o nó raiz muda.
					 */
					if (tos != 0)
					{
						stack[tos - 1]->left = q;
					}
					else
					{
						t->root = q;
					}

					/* atualizar as informações balanceadas dos nós p e q. */
					if (q->balance == 0)
					{
						p->balance = 1;
						q->balance = -1;
						break; /* Tree is balanced. */
					}
					else
					{
						p->balance = q->balance = 0;
					}

					/* A menos que q->balance == 0, as iterações continuarão, pois
					 * o comprimento do caminho mais longo diminuiu.
					 */
				}
				else
				{
					/* O balanceamento de (p, q) will be (2,-1)
					 */

					/* There is the following tree structure:
					 *  A - árvore direita filho de q.
					 *  B - árvore direita filho de r.
					 *  C - árvore esquerda filho de r.
					 *  D - árvore esquerda filho de p. (Deletion occurred in tree D)
					 */

					/* Para a rotação:
					 *  - A árvore B substitui o nó r como a esquerda filho de q.
					 *  - A árvore C substitui o nó q como a direita filho de p.
					 *  - Nó q substitui a árvore B como a direita filho de r.
					 *  - Nó p substitui a árvore C como a esquerda filho de r.
					 */
					r = q->left;
					q->left = r->right;
					p->right = r->left;
					r->right = q;
					r->left = p;
					if (r->balance == 1)
					{
						p->balance = -1;
						q->balance = 0;
					}
					else if (r->balance == -1)
					{
						p->balance = 0;
						q->balance = 1;
					}
					else
					{
						p->balance = q->balance = 0;
					}
					r->balance = 0;

					/* Um ponteiro filho do pai de p muda de p para r.
					 * Se p era a raiz, o nó raiz muda.
					 */
					if (tos != 0)
					{
						stack[tos - 1]->left = r;
					}
					else
					{
						t->root = r;
					}

					/* Continue com outras iterações, já que o comprimento de
					 * o caminho mais longo diminuiu.
					 */
				}
			}
		}
	}
	return return_item;
}
