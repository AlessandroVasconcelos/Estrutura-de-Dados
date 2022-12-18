#define D 5

typedef struct BTree BTree;

struct BTree
{
	int n;
	void *values[D - 1];
	BTree *child[D];
	BTree *parent;
	int (*compar)(void *, void *);
};

BTree *BTree_alloc(int (*compar)(void *, void *));
void BTree_free(BTree *b);
void BTree_insert(BTree *b, void *value);
void *BTree_search(BTree *b, void *value);
void *BTree_remove(BTree *b, void *value);
