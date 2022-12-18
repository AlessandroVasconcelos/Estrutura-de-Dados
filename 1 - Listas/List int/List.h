typedef struct List List;

/*criar uma lista*/
List *List_alloc();

/*liberar espaço na lista*/
void List_free(List *l);

/*inserir elemento na lista*/
void List_insert(List *l, int value);

/* insere elemento na lista de forma ordenada*/
void List_insertSorted(List *l, int value);

/*ordena a lista em ordem crescente*/
List *List_qsort(List *l);

/*remover elemento na lista*/
void List_remove(List *l, int value);

/*tamanho da lista*/
int List_getLenght(List *l);

/*mostra a lista*/
void List_print(List *l);

/** funcao recursiva para inverter a ordem dos elementos na lista encadeada.*/
int List_invert(List *l);

/** funcao recursiva para contar o número de elementos na lista encadeada.*/
int List_count(List *l);

/** Recebe duas listas como parametro e retorna uma nova lista com a
 *  uniao delas
 */
List *List_concat(List *l1, List *l2);

/** funcao remove maior da lista encadeada.*/
int List_removeMax(List *l);
