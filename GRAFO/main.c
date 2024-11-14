#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

void menu() {
    printf("\n--- Menu de Operacoes em Grafos ---\n");
    printf("1. Adicionar Aresta\n");
    printf("2. Remover Aresta\n");
    printf("3. Busca em Largura (BFS)\n");
    printf("4. Busca em Profundidade (DFS)\n");
    printf("5. Algoritmo de Dijkstra\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    int numVertices;
    printf("Digite o numero de vertices do grafo: ");
    scanf("%d", &numVertices);

    Graph* graph = createGraph(numVertices);
    int option, src, dest, weight;

    do {
        menu();
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Digite o vertice de origem: ");
                scanf("%d", &src);
                printf("Digite o vertice de destino: ");
                scanf("%d", &dest);
                printf("Digite o peso da aresta: ");
                scanf("%d", &weight);
                addEdge(graph, src, dest, weight);
                printf("Aresta adicionada de %d para %d com peso %d.\n", src, dest, weight);
                break;

            case 2:
                printf("Digite o vertice de origem: ");
                scanf("%d", &src);
                printf("Digite o vertice de destino: ");
                scanf("%d", &dest);
                removeEdge(graph, src, dest);
                printf("Aresta removida de %d para %d.\n", src, dest);
                break;

            case 3:
                printf("Digite o vertice inicial para BFS: ");
                scanf("%d", &src);
                printf("Resultado da BFS a partir do vertice %d: ", src);
                bfs(graph, src);
                printf("\n");
                break;

            case 4:
                printf("Digite o vertice inicial para DFS: ");
                scanf("%d", &src);
                printf("Resultado da DFS a partir do vertice %d: ", src);
                dfs(graph, src);
                printf("\n");
                break;

            case 5:
                printf("Digite o vertice inicial para Dijkstra: ");
                scanf("%d", &src);
                printf("Distâncias calculadas a partir do vertice %d:\n", src);
                dijkstra(graph, src);
                break;

            case 0:
                printf("Encerrando o programa e liberando a memoria...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    } while (option != 0);

    // Libera a memória do grafo antes de sair
    freeGraph(graph);

    return 0;
}
