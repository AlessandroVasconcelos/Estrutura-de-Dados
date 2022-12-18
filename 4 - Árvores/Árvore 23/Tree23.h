typedef struct Tree23 Tree23;

struct Tree23
{
	void *valueLeft;
	void *valueMiddle;
	void *valueRight;

	Tree23 *left;
	Tree23 *middleLeft;
	Tree23 *middleRight;
	Tree23 *right;

	Tree23 *parent;
	int (*compar)(void *, void *);
};

Tree23 *Tree23_alloc(int (*compar)(void *, void *));
void Tree23_free(Tree23 *t);
Tree23 *Tree23_search(Tree23 *t, void *item);
void Tree23_insert(Tree23 *t, void *value);
void *Tree23_remove(Tree23 *t, void *value);

/** Funcoes auxiliares */
int Tree23_nodeType(Tree23 *t);
Tree23 *Tree23_split4(Tree23 *t);
Tree23 *Tree23_split4Root(Tree23 *t);
Tree23 *Tree23_split4Parent2(Tree23 *t);
Tree23 *Tree23_split4Parent3(Tree23 *t);
