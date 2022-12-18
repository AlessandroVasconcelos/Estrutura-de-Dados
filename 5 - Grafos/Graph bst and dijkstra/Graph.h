typedef struct Graph Graph;
typedef struct Vertex Vertex;
typedef struct Edge Edge;

typedef struct
{
	Vertex *ant;
	int dist;
} Info;

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

// busca em profundidade, visita todos os vertices do grafo e guarda a ordem que cada vertice e encontrado.
Vertex **Graph_dfs(Graph *g, void *value, int (*cmp)(void *, void *));

// busca em largura, retorna a ordem em que os vertices são descobertos.
Vertex **Graph_bfs(Graph *g, void *value, int (*cmp)(void *, void *));

// calcula o caminho de custo minimo entre vertices de um grafo.
void Graph_dijkstra(Graph *g, int labelStart);
