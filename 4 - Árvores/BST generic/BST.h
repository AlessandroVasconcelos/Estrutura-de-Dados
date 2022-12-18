// BST = binary search tree = árvore binária de busca (generica)

typedef struct BST BST;
typedef struct BST_node BST_node;

struct BST_node
{
	// referencia para um valor generico.
	void *item;

	// referencia para um no a esquerda e outro no a direita.
	BST_node *left, *right;
};

struct BST
{
	// referencia para a raiz da BST.
	BST_node *root;
	int n;
	// ponteiro para um funcao de comparacao (todo no saiba como comparar as chaves dele).
	int (*compar)(const void *, const void *);
};

// Cria uma BST(no) aloca espaço.
BST *BST_alloc(int (*compar)(const void *, const void *));

// Destroi a BST(no) liberando-a da memoria.
void BST_free(BST *bst);

// Insere valor na BST.
void BST_insert(BST *bst, void *item);

// Pesquisa valor na BST.
void *BST_find(BST *bst, void *key);

// Remove valor na BST.
void *BST_delete(BST *bst, void *item);

// Mostra a BST.
void BST_print(BST_node *bst, void (*print)(void *));
