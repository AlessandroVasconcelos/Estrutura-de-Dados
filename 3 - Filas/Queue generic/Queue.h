typedef struct Queue Queue;

// (first-in first-out) o primeiro elemento a ser inserido, sera o primeiro a ser retirado.

/** Cria uma fila vazia*/
Queue *Queue_alloc(int size);

/** Destroi a fila liberando-a da memoria */
void Queue_free(Queue *q);

/** fila vazia */
int Queue_isEmpty(Queue *q);

/** fila cheia */
int Queue_isFull(Queue *q);

/** insere um elemento no final da fila - enfileirar  (push) */
void Queue_push(Queue *q, void *item);

/** acessar e remover elemento no inicio da fila - desenfileirar (pop);*/
void *Queue_pop(Queue *q);

/**acesso ao elemento no início da fila sem remover.*/
void *Queue_begin(Queue *q);

/**acesso ao elemento no final da fila sem remover.*/
void *Queue_end(Queue *q);

/* exibe os elementos da fila*/
void Queue_print(Queue *q, void (*print)(void *));

/* tamanho da fila*/
int Queue_length(Queue *q);