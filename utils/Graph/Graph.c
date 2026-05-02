#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ─── Adjacency-list graph (directed, unweighted) ───────────────────────────

typedef struct Node {
    int vertex;
    struct Node *next;
} Node;

typedef struct {
    int    numVertices;
    Node **adjLists;
    bool  *visited;
} Graph;

// ── helpers ────────────────────────────────────────────────────────────────

Node *newNode(int v)
{
    Node *n = malloc(sizeof *n);
    if (!n)
        return NULL;
    n->vertex = v;
    n->next   = NULL;
    return n;
}

Graph *createGraph(int vertices)
{
    Graph *g = malloc(sizeof *g);
    if (!g)
        return NULL;

    g->numVertices = vertices;
    g->adjLists    = malloc(vertices * sizeof *g->adjLists);
    g->visited     = malloc(vertices * sizeof *g->visited);

    for (int i = 0; i < vertices; i++) {
        g->adjLists[i] = NULL;
        g->visited[i]  = false;
    }

    return g;
}

void freeGraph(Graph *g)
{
    for (int i = 0; i < g->numVertices; i++) {
        Node *cur = g->adjLists[i];
        while (cur) {
            Node *tmp = cur;
            cur = cur->next; 
            free(tmp); 
        }
    }

    free(g->adjLists);
    free(g->visited);
    free(g);
}

// ── core operations ────────────────────────────────────────────────────────

void addEdge(Graph *g, int src, int dst)
{
    // src → dst
    Node *n       = newNode(dst);
    n->next       = g->adjLists[src];
    g->adjLists[src] = n;

    // dst → src  (remove these two lines to make it directed-only)
    n             = newNode(src);
    n->next       = g->adjLists[dst];
    g->adjLists[dst] = n;
}

void printGraph(const Graph *g)
{
    for (int i = 0; i < g->numVertices; i++) {
        printf("Vertex %d:", i);
        for (Node *cur = g->adjLists[i]; cur; cur = cur->next)
            printf(" → %d", cur->vertex);
        printf("\n");
    }
}

// ── BFS ───────────────────────────────────────────────────────────────────

void bfs(Graph *g, int start)
{
    // reset visited
    for (int i = 0; i < g->numVertices; i++)
        g->visited[i] = false;

    int *queue = malloc(g->numVertices * sizeof *queue);
    int head = 0, tail = 0;

    g->visited[start] = true;
    queue[tail++]     = start;

    printf("BFS from %d: ", start);
    while (head < tail) {
        int v = queue[head++];
        printf("%d ", v);
        for (Node *cur = g->adjLists[v]; cur; cur = cur->next) {
            if (!g->visited[cur->vertex]) {
                g->visited[cur->vertex] = true;
                queue[tail++] = cur->vertex;
            }
        }
    }

    printf("\n");
    free(queue);
}

// ── DFS ───────────────────────────────────────────────────────────────────

static void dfsHelper(Graph *g, int v)
{
    g->visited[v] = true;
    printf("%d ", v);
    for (Node *cur = g->adjLists[v]; cur; cur = cur->next)
        if (!g->visited[cur->vertex])
            dfsHelper(g, cur->vertex);
}

void dfs(Graph *g, int start)
{
    for (int i = 0; i < g->numVertices; i++)
        g->visited[i] = false;

    printf("DFS from %d: ", start);
    dfsHelper(g, start);
    printf("\n");
}

int main(void)
{
    Graph *g = createGraph(6);

    addEdge(g, 0, 1);
    addEdge(g, 0, 2);
    addEdge(g, 1, 3);
    addEdge(g, 2, 4);
    addEdge(g, 3, 5);
    addEdge(g, 4, 5);

    puts("=== Adjacency list ===");
    printGraph(g);
    puts("");

    bfs(g, 0);
    dfs(g, 0);

    freeGraph(g);
    return 0;
}
