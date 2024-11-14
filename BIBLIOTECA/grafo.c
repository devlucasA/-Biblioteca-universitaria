#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grafo.h"

// Cria um novo nó adjacente
AdjNode* createAdjNode(int dest, int weight) {
    AdjNode* newNode = (AdjNode*)malloc(sizeof(AdjNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Cria um novo grafo com um número específico de vértices
Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->array = (AdjList*)malloc(numVertices * sizeof(AdjList));

    for (int i = 0; i < numVertices; i++) {
        graph->array[i].head = NULL;
    }
    return graph;
}

// Adiciona uma aresta ao grafo
void addEdge(Graph* graph, int src, int dest, int weight) {
    AdjNode* newNode = createAdjNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Adiciona a aresta de dest para src, se o grafo for não-direcionado
    newNode = createAdjNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Remove uma aresta do grafo
void removeEdge(Graph* graph, int src, int dest) {
    AdjNode* temp = graph->array[src].head;
    AdjNode* prev = NULL;

    while (temp != NULL && temp->dest != dest) {
        prev = temp;
        temp = temp->next;
    }

    if (temp != NULL) {
        if (prev != NULL)
            prev->next = temp->next;
        else
            graph->array[src].head = temp->next;
        free(temp);
    }
}

// Busca em Largura (BFS)
void bfs(Graph* graph, int startVertex) {
    bool* visited = (bool*)malloc(graph->numVertices * sizeof(bool));
    for (int i = 0; i < graph->numVertices; i++)
        visited[i] = false;

    int queue[graph->numVertices];
    int front = 0, rear = 0;
    visited[startVertex] = true;
    queue[rear++] = startVertex;

    while (front < rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        AdjNode* temp = graph->array[currentVertex].head;
        while (temp) {
            int adjVertex = temp->dest;
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }

    free(visited);
}

// Função auxiliar para DFS
void dfsUtil(Graph* graph, int vertex, bool* visited) {
    visited[vertex] = true;
    printf("%d ", vertex);

    AdjNode* temp = graph->array[vertex].head;
    while (temp) {
        int adjVertex = temp->dest;
        if (!visited[adjVertex])
            dfsUtil(graph, adjVertex, visited);
        temp = temp->next;
    }
}

// Busca em Profundidade (DFS)
void dfs(Graph* graph, int startVertex) {
    bool* visited = (bool*)malloc(graph->numVertices * sizeof(bool));
    for (int i = 0; i < graph->numVertices; i++)
        visited[i] = false;

    dfsUtil(graph, startVertex, visited);
    free(visited);
}

// Algoritmo de Dijkstra
void dijkstra(Graph* graph, int startVertex) {
    int* dist = (int*)malloc(graph->numVertices * sizeof(int));
    bool* visited = (bool*)malloc(graph->numVertices * sizeof(bool));

    for (int i = 0; i < graph->numVertices; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    dist[startVertex] = 0;

    for (int i = 0; i < graph->numVertices - 1; i++) {
        int minDist = INT_MAX, minIndex;

        for (int v = 0; v < graph->numVertices; v++) {
            if (!visited[v] && dist[v] <= minDist) {
                minDist = dist[v];
                minIndex = v;
            }
        }

        int u = minIndex;
        visited[u] = true;

        AdjNode* temp = graph->array[u].head;
        while (temp) {
            int v = temp->dest;
            if (!visited[v] && dist[u] != INT_MAX && dist[u] + temp->weight < dist[v]) {
                dist[v] = dist[u] + temp->weight;
            }
            temp = temp->next;
        }
    }

    printf("Distâncias a partir do vértice %d:\n", startVertex);
    for (int i = 0; i < graph->numVertices; i++) {
        printf("Para %d: %d\n", i, dist[i]);
    }

    free(dist);
    free(visited);
}

// Função para liberar a memória do grafo
void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        AdjNode* temp = graph->array[i].head;
        while (temp) {
            AdjNode* next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(graph->array);
    free(graph);
}
