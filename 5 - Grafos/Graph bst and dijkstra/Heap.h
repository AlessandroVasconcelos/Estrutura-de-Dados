typedef struct Heap Heap;

struct Heap
{
	int n, max;
	void **itens;
	int (*compar)(void *, void *);
};

Heap *Heap_alloc(int max, int (*compar)(void *, void *));
void Heap_free(Heap *h);
void *Heap_remove(Heap *h);
void Heap_insert(Heap *h, void *item);
void Heap_increase(Heap *h, int i, void *item);
void Heap_decrease(Heap *h, int i, void *item);
