
/*
 * MAIN.CPP : Graph examples
 *
 * Adapted from Algorithms in C Part 5, Robert Sedgewick
 * Copyright(c) 2002 by Addison-Wesley
 */

#include <iostream>
#include <stdlib.h>
#include <memory.h>

#define maxV 50			/* maximum number of vertices */

/////////////////////////////////////////////////////////////////////////////////////////////
int **matrixalloc(int r, int c)
{
    int i;

    int **t = (int**)malloc(r * sizeof(int*));
    for (i = 0; i < r; i++)
        t[i] = (int*)malloc(c * sizeof(int));
    return t;
}

/////////////////////////////////////////////////////////////////////////////////////////////
int **matrixinit(int r, int c, int val)
{
    int i, j;

    int **t = matrixalloc(r, c);
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            t[i][j] = val;
    return t;
}

/////////////////////////////////////////////////////////////////////////////////////////////
int **matrixcopy(int **src, int r, int c)
{
    int i, j;

    int **t = matrixalloc(r, c);
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            t[i][j] = src[i][j];
    return t;
}

/////////////////////////////////////////////////////////////////////////////////////////////
struct Edge {
    Edge(int, int);
    int v;
    int w;
};

/////////////////////////////////////////////////////////////////////////////////////////////
Edge::Edge(int V, int W)
    : v(V), w(W)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////
class Graph
{
// Construction / Destruction
public:
    Graph(int);
    Graph(const Graph &G);
    virtual ~Graph();

// Interface
    void insertEdge(const Edge &E);
    void removeEdge(const Edge &E);
    int edges(Edge []);

    int vertices() const
    {
        return V;
    }
    int degree(int v) const
    {
        return deg[v];
    }
    int edges() const
    {
        return E;
    }
    bool isEdge(int v, int w) const;
    bool path(int v, int w) const;

    Graph & operator = (const Graph &rhs);

// Implementation
private:
    bool path(int v, int w, int visited[]) const;

    int V;		// number of vertices
    int E;		// number of edges
    int **adj;	// adjacency matrix
    int *deg;	// degree of each vertex
};

/////////////////////////////////////////////////////////////////////////////////////////////
Graph::Graph(int v)
    : V(v), E(0)
{
    adj = matrixinit(V, V, 0);
    deg = (int*)malloc(sizeof(int) * V);
    memcpy(deg, 0, sizeof(int) * V);
}

/////////////////////////////////////////////////////////////////////////////////////////////
Graph::Graph(const Graph &G)
{
    *this = G;
}

/////////////////////////////////////////////////////////////////////////////////////////////
Graph& Graph::operator = (const Graph & rhs)
{
    if (this != &rhs) {
        V = rhs.V;
        E = rhs.E;
        adj = matrixcopy(rhs.adj, rhs.vertices(), rhs.vertices());
        deg = (int*)malloc(sizeof(int) * V);
        memcpy(deg, rhs.deg, sizeof(int) * V);
    }

    return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////////
Graph::~Graph()
{
    free(adj);
    free(deg);
}

/////////////////////////////////////////////////////////////////////////////////////////////
void Graph::insertEdge(const Edge &e)
{
    int v = e.v, w = e.w;

    if (adj[v][w] == 0) {
        deg[v]++, deg[w]++, E++;
    }
    adj[v][w] = adj[w][v] = 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////
void Graph::removeEdge(const Edge &e)
{
    int v = e.v, w = e.w;

    if (adj[v][w] == 1) {
        deg[v]--, deg[w]--, E--;
    }
    adj[v][w] = adj[w][v] = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////
int Graph::edges(Edge a[])
{
    int v, w, E = 0;
    for (v = 0; v < V; v++)
        for (w = v + 1; w < V; w++)
            if (adj[v][w] == 1)
                a[E++] = Edge(v, w);
    return E;
}

/////////////////////////////////////////////////////////////////////////////////////////////
bool Graph::isEdge(int v, int w) const
{
    if (v >= V || w >= V)
        return false;
    return (adj[v][w] == 1);
}

/////////////////////////////////////////////////////////////////////////////////////////////
bool Graph::path(int v, int w) const
{
    if (v >= V || w >= V)
        return false;

    int visited[maxV];
    memset(visited, 0, sizeof(visited));

    return path(v, w, visited);
}

/////////////////////////////////////////////////////////////////////////////////////////////
bool Graph::path(int v, int w, int visited[]) const
{
    int t;
    if (v == w) return true;
    visited[v] = 1;
    for (t = 0; t < V; t++)
        if (adj[v][t] == 1)
            if (visited[t] == 0)
                if (path(t, w, visited)) return true;

    return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////
int randV(const Graph &G)
{
    return (int)(G.vertices() * (rand() / (RAND_MAX + 1.0)));
}

/////////////////////////////////////////////////////////////////////////////////////////////
Graph GRAPHrand(int V, int E)
{
    Graph G(V);
    while (G.edges() < E)
        G.insertEdge(Edge(randV(G), randV(G)));

    return G;
}

/////////////////////////////////////////////////////////////////////////////////////////////
void GRAPHprint(const Graph &G)
{
    int i, j;
    for (i = 0; i < G.vertices(); i++) {
        printf("%2d:", i);
        for (j = 0; j < G.vertices(); j++)
            if (G.isEdge(i, j)) printf(" %2d", j);
        printf("\n");
    }
}

typedef void (*menufunc)();
static Graph * g_Graph;

#define MAXLINE 1024

/////////////////////////////////////////////////////////////////////////////////////////////
void cleanup()
{
    if (g_Graph) {
        delete g_Graph;
        g_Graph = 0;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////
void graphgen()
{
    int N, V, E;

    cout << "V, E: ";

    char line[MAXLINE] = { 0 };
    cin.getline(line, MAXLINE);

    N = sscanf(line, "%d, %d", &V, &E);
    if (N != 2) {
        cerr << "invalid format." << endl;
        return;
    }

    if (V > maxV || E > (V + V)) {
        cerr << "vertices must be less than " << maxV <<
             ", and edges must not exceed 2V." << endl;
        return;
    }

    cleanup();

    g_Graph = new Graph(GRAPHrand(V, E));
}

/////////////////////////////////////////////////////////////////////////////////////////////
void graphprint()
{
    if (g_Graph == 0) {
        cerr << "no graph currently exists." << endl;
        return;
    }

    GRAPHprint(*g_Graph);
}

/////////////////////////////////////////////////////////////////////////////////////////////
void graphpath()
{
    int v, w, N;

    if (g_Graph == 0) {
        cerr << "no graph currently exists." << endl;
        return;
    }

    cout << "v, w: ";

    char line[MAXLINE] = { 0 };
    cin.getline(line, MAXLINE);

    N = sscanf(line, "%d, %d", &v, &w);
    if (N != 2) {
        cerr << "invalid format." << endl;
        return;
    }

    if (g_Graph->path(v, w))
        cout << "path exists!" << endl;
    else
        cout << "no path exists." << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
void headerprint()
{
    cout << "Graph Algorithms Example Program" << endl;
    cout << "Adapted from Algorithms in C, Part 5 Graph Algorithms" << endl;
    cout << "Copyright(c) 2002, Addison-Wesley" << endl << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
void menuprint()
{
    cout << "(1) Generate a new graph" << endl;
    cout << "(2) Print current graph" << endl;
    cout << "(3) Find a path" << endl;
    cout << "(4) Exit" << endl;
    cout << "Choose: ";
}

/////////////////////////////////////////////////////////////////////////////////////////////
menufunc menuoption()
{
    char line[MAXLINE] = { 0 };
    cin.getline(line, MAXLINE);

    int N = atoi(line);
    switch (N) {
    case 1:
        return graphgen;
    case 2:
        return graphprint;
    case 3:
        return graphpath;
    }

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// driver program
int main (int argc, const char * argv[])
{
    menufunc pfn;

    headerprint();

    for (;;) {
        menuprint();
        pfn = menuoption();
        if (pfn == 0)
            break;

        (*pfn)();
    }

    cleanup();

    return 0;
}
