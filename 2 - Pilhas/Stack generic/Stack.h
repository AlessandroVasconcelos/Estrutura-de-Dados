typedef struct Stack Stack;

//(last-in first-out), onde o ultimo(last) elemento a ser inserido, será o primeiro(first) a ser retirado.

/** Cria uma pilha */
Stack *Stack_alloc(int size);

/** Destroi a pilha liberando-a da memoria */
void Stack_free(Stack *stack);

/** pilha vazia */
int Stack_isEmpty(Stack *stack);

/** pilha cheia */
int Stack_isFull(Stack *stack);

/** Insere um elemento do topo da pilha - empilhar (push) */
void Stack_push(Stack *stack, void *element);

/** remove um elemento do topo da pilha - desempilhar (pop);*/
void *Stack_pop(Stack *stack);

/** acesso ao elemento no topo da pilha sem sua remocao*/
void *Stack_top(Stack *stack);

/* retorna o tamanho da pilha*/
int Stack_length(Stack *s);

/* exibe os elementos da pilha*/
void Stack_print(Stack *s, void (*print)(void *));