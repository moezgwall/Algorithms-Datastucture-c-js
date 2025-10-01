#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int vertex;
    struct Node *next;
} Node;

typedef struct Graph
{
    int nVertices;
    Node **adjList;
} Graph;

Node *createNode(int v)
{
    Node *nNode = (Node *)malloc(sizeof(Node));
    nNode->vertex = v;
    nNode->next = NULL;
    return nNode;
}

Graph *createGraph(int v)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->nVertices = v;
    graph->adjList = (Node **)malloc(sizeof(Node *) * v);

    for (int i = 0; i < v; i++)
    {
        graph->adjList[i] = NULL;
    }
    return graph;
}

void addEdge(Graph *g, int source, int dest)
{
    Node *nNode = createNode(dest);
    nNode->next = g->adjList[source];
    g->adjList[source] = nNode;

    nNode = createNode(source);
    nNode->next = g->adjList[dest];
    g->adjList[dest] = nNode;
}

void show(Graph *p)
{
    if (!p)
        return;

    for (int i = 0; i < p->nVertices; ++i)
    {
        Node *node = p->adjList[i];
        printf("Vertex [%d]", i);
        while (node)
        {
            printf(" |--> [%d]", node->vertex);
            node = node->next;
        }
        printf("\n");
    }
}

void clean(Graph *g)
{
    if (!g)
        return;
    free(g->adjList);
    free(g);
}

int main()
{
    Graph *g = createGraph(3);

    addEdge(g, 0, 1);
    addEdge(g, 1, 6);
    addEdge(g, 0, 2);

    show(g);
    clean(g);

    return 0;
}