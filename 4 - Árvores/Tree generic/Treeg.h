typedef struct Tree Tree;

struct Tree
{
	void *value;
	Tree *left;
	Tree *right;
};

// cria uma arvore(no) aloca espaço.
Tree *Tree_alloc(void *value, Tree *left, Tree *right);

// Destroi a arvore(no) liberando-a da memoria.
void Tree_free(Tree *t);

void *Tree_getValue(Tree *t);

// mostra os filhos na esquerda.
Tree *Tree_getLeft(Tree *t);

// mostra os filhos na direita.
Tree *Tree_getRight(Tree *t);

// adiciona um novo no.
void Tree_setValue(Tree *t, void *value);

// adiciona um no a esquerda(value), com dois filhos NULL.
void Tree_setLeft(Tree *t, void *value);

// adiciona um no a direita(value), com dois filhos NULL.
void Tree_setRight(Tree *t, void *value);

void Tree_print(Tree *t, void (*print)(void *));
void Tree_print_main(Tree *t, void (*print)(void *));

int Tree_alt(Tree *t);
void *Tree_getParent(Tree *t, void *value, int (*comparStr)(const void *, const void *));
void Tree_calcular(Tree *t, int *resultado, int *tam, int *left, int *right);

// funcao principal para pesquisar value na arvore.
Tree *Tree_find_main(Tree *t, void *value, int (*compar)(void *, void *), void (*print_char)(void *));
// pesquisar value na arvore.
Tree *Tree_find(Tree *t, void *value, int (*compar)(void *, void *));

// percurso Em ordem.
void Tree_inOrder(Tree *t, void (*process)(void *));
// percurso Pré-ordem.
void Tree_preOrder(Tree *t, void (*process)(void *));
// percurso Pós-ordem.
void Tree_postOrder(Tree *t, void (*process)(void *));

void Tree_print_level_main(Tree *bst, void (*print)(void *));
void Tree_print_level(Tree *bst, void (*print)(void *), int level, char c);

// funcao principal da altura da arvore.
void Tree_height_main(Tree *t);
// altura da arvore.
int Tree_height(Tree *t);

void Tree_eval_main(Tree *t);
int Tree_eval(Tree *t);
