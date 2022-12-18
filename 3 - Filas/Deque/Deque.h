typedef struct Deque Deque;
typedef struct DequeNode DequeNode;

struct DequeNode
{
	void *value;
	DequeNode *prev, *next;
};

struct Deque
{
	int length;
	DequeNode *front, *back;
};

Deque *Deque_alloc();
void Deque_free(Deque *d);
void Deque_pushFront(Deque *d, void *value);
void Deque_pushBack(Deque *d, void *value);
void *Deque_popFront(Deque *d);
void *Deque_popBack(Deque *d);
