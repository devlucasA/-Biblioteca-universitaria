#ifndef GRAPH_H
#define GRAPH_H

#include <limits.h>

// Estrutura para o nó adjacente (representa uma aresta no grafo)
typedef struct AdjNode {
    int dest;
    int weight;
    struct AdjNode* next;
    void* data;
} AdjNode;

// Estrutura para a lista de adjacência de um vértice
typedef struct AdjList {
    AdjNode* head;
} AdjList;

// Estrutura para o grafo
typedef struct Graph {
    int numVertices;
    AdjList* array;
} Graph;

// Funções para manipulação do grafo

// Cria um novo grafo com um número de vértices
Graph* createGraph(int numVertices);

// Adiciona uma aresta ao grafo
void addEdge(Graph* graph, int src, int dest, int weight);

// Remove uma aresta do grafo
void removeEdge(Graph* graph, int src, int dest);

// Busca em Largura (BFS)
void bfs(Graph* graph, int startVertex);

// Busca em Profundidade (DFS)
void dfs(Graph* graph, int startVertex);

// Algoritmo de Dijkstra
void dijkstra(Graph* graph, int startVertex);

// Libera a memória do grafo
void freeGraph(Graph* graph);

#endif // GRAPH_H
