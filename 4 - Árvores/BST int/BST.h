// BST = binary search tree = árvore binária de busca (inteiros)

typedef struct BST BST;

struct BST
{
    int value;
    BST *left;
    BST *right;
};

// Cria uma BST(no) aloca espaço.
BST *BST_alloc();

// Destroi a BST(no) liberando-a da memoria.
void BST_free(BST *bst);

// Insere valor na BST.
void BST_insert(BST *bst, int value);

// Pesquisa valor na BST.
BST *BST_search(BST *bst, int value);

// Remove valor na BST.
BST *BST_remove(BST *bst, int value);

// Mostra a BST.
void BST_print(BST *bst);
