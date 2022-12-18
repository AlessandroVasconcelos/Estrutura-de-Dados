#ifndef TREE23_H
#define TREE23_H
/*
 *   Shane Saunders
 */

/* Tamanho da pilha. Especifica a profundidade máxima da árvore suportada.
 * Consulte Tree23_alloc() em Tree23.c.
 */
#define TREE23_STACK_SIZE 1000

/* Existem dois tipos de ponteiros filhos para nós na árvore 2-3. O primeiro
 * kind são ponteiros para outros nós. O segundo tipo são ponteiros para a folha
 * itens (itens de dados) na árvore.
 */
struct Tree23_node;

typedef union Tree23_link
{
	struct Tree23_node *node; /* link para o nodo interno... */
	void *item;				  /* ... ou um link para um item de dados. */
} Tree23_link;

/* Um nó na árvore 2-3 mantém duas chaves e três ponteiros filhos.
 * Um nó na árvore 2-3 tem entre dois e três filhos, exceto o
 * caso especial onde é o nó raiz de uma árvore contendo apenas 0 ou 1
 * nós. Quando um nó tem dois filhos, seus ponteiros filho esquerdo e do meio são
 * usado e seu ponteiro filho direito é NULL. Para um nó que tem três
 * filhos, todos os ponteiros filhos são usados.
 *
 * Os itens de dados em uma árvore dois-três são todos armazenados no nível mais baixo da
 * árvore como itens de folha. Um nó cujos filhos são itens folha tem seu link_kind
 * campo definido como LEAF_LINK. Se os filhos do nó forem outros nós, então seu
 * o parâmetro link_kind será definido como INTERNAL_LINK.
 *
 * Um nó na árvore 2-3 tem duas chaves:
 * key_item1 - aponta para o item com a menor chave entre os itens do
 * nós da subárvore filho do meio. Para o caso especial em que um
 * nó raiz contém apenas 0 ou 1 nós, key_item1 é NULL.
 * key_item2 - aponta para o item com a menor chave entre os itens do
 * nós da subárvore filho direito. Se não houver filho certo, então
 * key_item2 é NULL.
 *
 * As propriedades das árvores filhas de um nó em uma árvore 2-3 são:
 * - os itens de dados armazenados na subárvore do filho direito
 * chave(key_item2) <= chave(i).
 * - os itens de dados armazenados na subárvore filho do meio têm
 * key(key_item1) <= key(i) < key(key_item2).
 * - os itens de dados armazenados na subárvore filha esquerda
 * chave(i) < chave(chave_item2).
 */
typedef struct Tree23_node
{
	void *key_item1, *key_item2;
	Tree23_link left, middle, right;
	enum
	{
		LEAF_LINK,
		INTERNAL_LINK
	} link_kind;
} Tree23_node;

/* The 2-3 O tipo de estrutura em árvore possui os seguintes campos:
 * root - um ponteiro para o nó raiz.
 * comparar - um ponteiro para a função a ser usada para comparar as chaves dos itens na árvore.
 * n - o número de itens de dados armazenados na árvore.
 * altura - a altura da árvore.
 * min_item - um ponteiro para o item mínimo na árvore 2-3.
 */
typedef struct Tree23
{
	Tree23_node *root;
	int (*compar)(const void *, const void *);
	int n;
	void *min_item;
	Tree23_node **stack;
	signed char *path_info;
} Tree23;

/* Tree23_alloc() - Aloca espaço para uma árvore 2-3 e retorna um ponteiro para
 * isto. A função compar compara as chaves de dois itens e retorna um
 * negativo, zero ou número inteiro positivo, dependendo se o primeiro item é
 * menor que, igual ou maior que o segundo.
 */
Tree23 *Tree23_alloc(int (*compar)(const void *, const void *));

/* Tree23_free() - Libera o espaço usado pela árvore 2-3 apontada por t. */
void Tree23_free(Tree23 *t);

/* Tree23_insert() - Insere um item na árvore 2-3 apontada por t,
 * de acordo com o valor de sua chave. A chave de um item na árvore 2-3 deve
 * ser único entre os itens da árvore. Se um item com a mesma chave já
 * existe na árvore, um ponteiro para esse item é retornado. Caso contrário, NULL é
 * retornado, indicando que a inserção foi bem-sucedida.
 */
void *Tree23_insert(Tree23 *t, void *item);

/* Tree23_find() - Encontre um item na árvore 2-3 com a mesma chave do
 * item apontado por `key_item'. Retorna um ponteiro para o item encontrado, ou NULL
 * se nenhum item foi encontrado.
 */
void *Tree23_find(Tree23 *t, void *key_item);

/* Tree23_find_min() -Retorna um ponteiro para o item mínimo na árvore 2-3
 * apontado por t. Se não houver itens na árvore, um ponteiro NULL será
 * retornou.
 */
void *Tree23_find_min(Tree23 *t);

/* Tree23_delete() - Exclua o item na árvore 2-3 com a mesma chave que
 * o item apontado por `key_item'. Retorna um ponteiro para o item excluído,
 * e NULL se nenhum item foi encontrado.
 */
void *Tree23_delete(Tree23 *t, void *key_item);

/* Tree23_delete_min() - Exclui o item com a menor chave do
 * árvore de pesquisa binária apontada por t. Retorna um ponteiro para o item excluído.
 * Retorna um ponteiro NULL se não houver itens na árvore.
 */
void *Tree23_delete_min(Tree23 *t);

#endif
