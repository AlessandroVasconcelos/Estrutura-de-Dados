typedef struct Graph Graph;
typedef struct Vertex Vertex;
typedef struct Edge Edge;

// estrutura da Aresta.
struct Edge
{
	int label;
	void *value;
	// cauda do vertice.
	Vertex *tail;
	// cabeca do vertice.
	Vertex *head;
	// proxima aresta.
	Edge *next;
};

// estrutura do Vertice.
struct Vertex
{
	int n;
	int label;
	int visited;
	void *value;
	// primeiro aresta.
	Edge *first;
	// ultimo aresta.
	Edge *last;
	// proximo vertice.
	Vertex *next;
};

// estrutura do Grafo.
struct Graph
{
	int n;
	// primeiro vertice.
	Vertex *first;
	// ultimo vertce.
	Vertex *last;
};

// aloca espaco de memoria para o grafo.
Graph *Graph_alloc();

// libera espaco de memoria do grafo.
void Graph_free(Graph *g);

// insere o vertice no grafo.
void Graph_insertVertex(Graph *g, void *value);

// insere a aresta no grafo atraves da posicao do vertice.
void Graph_insertEdge(Graph *g, int label1, int label2, void *value);

// remove o vertice do grafo.
void Graph_removeVertex(Graph *g, int label);

// remove a aresta do grafo atraves da posicao do vertice.
void Graph_removeEdge(Graph *g, int label1, int label2);

// pesquisa o rotulo no grafo.
Vertex *Graph_findByLabel(Graph *g, int label);

// pesquisa o valor no grafo.
Vertex *Graph_findByValue(Graph *g, void *value, int (*cmp)(void *, void *));

// exibe o grafo.
void Graph_print(Graph *g, void (*print)(void *value));