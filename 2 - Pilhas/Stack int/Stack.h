typedef struct Stack Stack;

//(last-in first-out) o ultimo elemento a ser inserido, será o primeiro a ser retirado.

/** Cria uma pilha vazia */
Stack *Stack_alloc(int size);

/** Destroi a pilha liberando-a da memoria */
void Stack_free(Stack *stack);

/** pilha vazia */
int Stack_isEmpty(Stack *stack);

/** pilha cheia */
int Stack_isFull(Stack *stack);

/** Insere um elemento do topo da pilha - empilhar (push) */
void Stack_push(Stack *stack, int element);

/** remove um elemento do topo da pilha - desempilhar (pop);*/
int Stack_pop(Stack *stack);

/** acesso ao elemento no topo da pilha sem sua remocao*/
int Stack_top(Stack *stack);

/* retorna o tamanho da pilha*/
int Stack_length(Stack *s);

/* exibe os elementos da pilha*/
void Stack_print(Stack *s);