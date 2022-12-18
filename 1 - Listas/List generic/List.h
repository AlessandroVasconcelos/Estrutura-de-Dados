typedef struct List List;

/** Cria uma nova lista */
List *List_alloc();

/** Destroi a lista liberando-a da memoria */
void List_free(List *l);

/** insere elemento na lista */
void List_insert(List *l, void *value);

/** remove elemento na lista */
void *List_remove(List *l, void *value, int (*compar)(void *, void *));

/** remove elemento especifico na lista*/
void *List_remove1(List *l, void *value, int (*compar)(void *, void *));

/** Busca um elemento especifico na lista e retorna este elemento. Tem
 *  o funcionamento semelhante a funcao List_findAndRemove, mas não
 *  remove o elemento buscado.
 */
void *List_find(List *l, void *value, int (*compar)(void *, void *));

/* retorna o tamanho da lista*/
int List_getLenght(List *l);

/** Imprime os valores da lista.
 *  Parametros:
 *  - l: uma lista,
 *  - print: ponteiro para uma funcao que imprime um elemento.
 *           Esta funcao e' chamada repetidamente para imprimir todos
 *           os elementos da lista.
 *
 *           Deve seguir o seguinte prototipo:
 *                     void print (void* p);
 *
 *           Usando um ponteiro como argumento (convertido para void *).
 */
void List_print(List *l, void (*print)(void *));

/** Insere um elemento no inicio da lista */
void List_insertBegin(List *l, void *value);

/** Insere um elemento no final da lista */
void List_insertEnd(List *l, void *value);

/** Busca e remove um elemento especifico na lista, e retorna este elemento.
 *  Parâmetros:
 *  - l:    uma lista,
 *  - value:   valor usado como referencia para a busca,
 *  - compar:  ponteiro para uma funcao que compara dois elementos.
 *             Esta funcao e' chamada repetidamente para comparar o
 *             parâmetro 'value' com os elementos da lista.
 *
 *             Deve seguir o seguinte prototipo:
 *                       int compar(void* p1, void* p2);
 *
 *             Usando dois ponteiros como argumentos (ambos convertidos
 *             para void *).
 *             A funcao define a igualdade entre os elementos retornando:
 *                  +-----------------+-----------------------+
 *                  | VALOR RETORNADO |        DESCRICAO      |
 *                  +-----------------+-----------------------+
 *                  |        1        | o primeiro e' maior   |
 *                  |        0        | os valores sao iguais |
 *                  |       -1        | o segundo e' maior    |
 *                  +-----------------+-----------------------+
 */
void *List_findAndRemove(List *l, void *value, int (*compar)(void *, void *));

/** Recebe duas listas como parametro e retorna uma nova lista com a
 *  uniao delas
 */
List *List_concat(List *l1, List *l2);

/** Recebe uma lista como parametro e retorna a uma nova lista ordenada. Usa
 *  uma funcao de comparacao semelhante a presente na funcao List_findAndRemove.
 */
List *List_qsort(List *l, int (*compar)(void *, void *));

/** Insere o elemento value na lista l de forma ordenada Usa uma funcao de
 *  comparacao semelhante a presente na funcao List_findAndRemove.
 */
void List_insertSorted(List *l, void *value, int (*compar)(void *, void *));

/** Remove maior elemento da lista e retorna ele. */
void *List_removeMaior(List *l, int (*compar)(void *, void *));

/** Remove um elemento no inicio da lista. */
void *List_removeBegin(List *l);

/** Remove um elemento no final da lista. */
void *List_removeEnd(List *l);

/** funcao recursiva para contar o número de elementos na lista encadeada.*/
int List_count(List *l);

/** funcao recursiva para inverter a ordem dos elementos na lista encadeada.*/
List *List_invert(List *l);