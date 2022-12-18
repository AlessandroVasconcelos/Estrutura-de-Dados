/*** File AVL.h - AVL Tree ***/
/*
 * Shane Saunders
 */
#ifndef AVL_H
#define AVL_H

/*  Tamanho da pilha usada para armazenar o caminho da travesed pela árvore.
 *  Isso deve ser definido para ser grande o suficiente para acomodar o máximo
 *  profundidade prática da árvore que poderia ser esperada. */
#define AVL_STACK_SIZE 1000

/* Tipo de estrutura para nós na árvore AVL. */
typedef struct AVL_node
{
	void *item;
	struct AVL_node *left, *right;
	signed char balance;
} AVL_node;

/* Tipo de estrutura para a árvore AVL. */
typedef struct AVL
{
	AVL_node *root;
	int n;
	int (*compar)(const void *, const void *);
	AVL_node **stack;
	signed char *path_info;
} AVL;

/* AVL_ALLOC () - aloca espaço para uma árvore AVL e retorna um ponteiro para ela.
 * A função compar compara as keys de dois itens e retorna um negativo, zero, ou número inteiro positivo,
 * dependendo se o primeiro item é menor que, igual a, ou maior que o segundo.
 */
AVL *AVL_alloc(int (*compar)(const void *, const void *));

/* Avl_free () - libera espaço usado pela árvore AVL apontada por t. */
void AVL_free(AVL *t);

/* Avl_insert () - insere um item na árvore AVL apontada por t, de acordo com o valor é a key.
 * A key de um item na árvore AVL deve ser único entre os itens na árvore.
 * Se um item com a mesma key já existe na árvore, um ponteiro para esse item é retornado.
 * Caso contrário, NULL é retornado, indicando que a inserção foi bem-sucedida.
 */
void *AVL_insert(AVL *t, void *item);

/* Avl_find () - Encontra um item na árvore AVL com a mesma key que o item apontado por "key_item".
 * Retorna um ponteiro para o item encontrado, ou NULL se nenhum item foi encontrado.
 */
void *AVL_find(AVL *t, void *key_item);

/* Avl_find_min () - retorna um ponteiro para o item mínimo no AVL
 * Árvore apontada por t. Se não houver itens na árvore, um ponteiro NULL é retornado.
 */
void *AVL_find_min(AVL *t);

/* AVL_delete() - Exclui o primeiro item encontrado na árvore AVL com a mesma key que o item apontado por "key_item".
 * Retorna um ponteiro para o item excluído e NULL se nenhum item foi encontrado.
 */
void *AVL_delete(AVL *t, void *key_item);

/* Avl_delete_min () - Exclui o item com a menor key da Árvore AVL apontada por t.
 * Retorna um ponteiro para o item excluído.
 * Retorna um ponteiro NULL se não houver itens na árvore.
 */
void *AVL_delete_min(AVL *t);

#endif
