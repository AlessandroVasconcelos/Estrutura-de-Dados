typedef struct Heap Heap;

struct Heap
{
	int n, max;
	void **itens;
	int (*compar)(const void *, const void *);
};

Heap *Heap_alloc(int max, int (*compar)(const void *, const void *));
void Heap_free(Heap *h);
void Heap_insert(Heap *h, void *value);
void *Heap_remove(Heap *h);
void Heap_changeValue(Heap *h, int m, void *value);
Heap *Heap_build(void *arr, int length, int max, int (*compar)(const void *, const void *));
