// BST = binary search tree = árvore binária de busca (generica)

typedef struct BST BST;

struct BST
{
    // referencia para um valor generico.
    void *value;

    // referencia para um no a esquerda.
    BST *left;

    // referencia para um no a direita.
    BST *right;

    // ponteiro para um funcao de comparacao (todo no saiba como comparar as chaves dele).
    int (*compar)(void *, void *);
};

// Cria uma BST(no) aloca espaço.
BST *BST_alloc(int (*compar)(void *, void *));

// Destroi a BST(no) liberando-a da memoria.
void BST_free(BST *bst);

// Insere valor na BST.
void BST_insert(BST *bstree, void *value);

// Pesquisa valor na BST.
void *BST_search(BST *bst, void *value);

// Remove valor na BST.
void *BST_remove(BST *bst, void *value);

// Mostra a BST.
void BST_print(BST *bst, void (*print)(void *));
