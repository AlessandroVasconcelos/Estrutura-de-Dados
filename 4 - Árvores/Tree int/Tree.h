typedef struct Tree Tree;

struct Tree
{
	int value;
	Tree *left;
	Tree *right;
};

// Cria uma arvore(no) aloca espaço.
Tree *Tree_alloc(int value, Tree *left, Tree *right);
// Destroi a arvore(no) liberando-a da memoria.
void Tree_free(Tree *t);
// Mostra a arvore.
void Tree_print(Tree *t);