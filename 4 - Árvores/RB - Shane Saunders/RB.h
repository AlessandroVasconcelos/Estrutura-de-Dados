/*** File RB.h - Red-Black Tree ***/
/*
 *   Shane Saunders
 */
#ifndef RB_H
#define RB_H
#define RB_STACK_SIZE 1000

typedef enum
{
	Red,
	Black
} RB_colour;

/* Tipo de estrutura para nós na árvore vermelho e preto.*/
typedef struct RB_node
{
	void *item;
	struct RB_node *left, *right;
	RB_colour colour;
} RB_node;

/* Tipo de estrutura para a árvore vermelho e preto. */
typedef struct RB
{
	RB_node *root;
	int n;
	int (*compar)(const void *, const void *);
	RB_node **stack;
} RB;

/* RB_alloc() - Aloca espaço para uma árvore vermelho e preto e retorna um ponteiro para ela.
 * A função compar compara as chaves de dois itens e retorna um
 * número inteiro negativo, zero ou positivo, dependendo se o primeiro item é menor que, igual ou maior que o segundo.
 */
RB *RB_alloc(int (*compar)(const void *, const void *));

/* RB_free() - Libera espaço usado pela árvore rubro-negra apontada por t.*/
void RB_free(RB *t);

/* RB_insert() - Insere um item na árvore vermelho e preto apontada por t,
 * de acordo com o valor de sua chave. A chave de um item no vermelho e preto
 * a árvore deve ser única entre os itens da árvore. Se um item com a mesma chave
 * já existe na árvore, um ponteiro para esse item é retornado.
 * Por outro lado, NULL é retornado, indicando que a inserção foi bem-sucedida.
 */
void *RB_insert(RB *t, void *item);

/* RB_find() - Encontra um item na árvore  vermelho e preto com a mesma chave que o item apontado por "key_item".
 * Retorna um ponteiro para o item encontrado ou NULL se nenhum item foi encontrado.
 */
void *RB_find(RB *t, void *key_item);

/* RB_find_min() - Retorna um ponteiro para o item mínimo da árvore vermelho e preto apontada por t.
 * Se não houver itens na árvore, um ponteiro NULL é retornado.
 */
void *RB_find_min(RB *t);

/* RB_delete() - Exclui um item na árvore vermelho e preto com a mesma chave que o item apontado por "key_item".
 * Retorna um ponteiro para o item excluído, e NULL se nenhum item foi encontrado.
 */
void *RB_delete(RB *t, void *key_item);

/* RB_delete_min() - Exclui o item com a menor chave do binário
 * árvore de busca apontada por t. Retorna um ponteiro para o item excluído.
 * Retorna um ponteiro NULL se não houver itens na árvore.
 */
void *RB_delete_min(RB *t);

#endif
