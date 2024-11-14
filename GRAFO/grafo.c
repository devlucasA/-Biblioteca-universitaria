#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

// Estrutura de um livro
typedef struct Livro {
    int isbn;
    char titulo[100];
    char autor[100];
    int ano_publicacao;
    int quantidade;
} Livro;

// Estrutura de uma aresta para a relação entre livros
typedef struct Aresta {
    int peso;   // Peso da relação entre dois livros 
    struct NoAdjacencia *destino;  // Ponteiro para o vértice relacionado
} Aresta;

// Estrutura de um nó na lista de adjacências
typedef struct NoAdjacencia {
    Livro *livro;     // Vértice que representa o livro
    Aresta *arestas; // Lista de arestas para relações com outros livros
    int num_arestas;     // Número de arestas
} NoAdjacencia;

// Grafo de livros com lista de adjacências
typedef struct Grafo {
    NoAdjacencia **vertices; // Lista de vértices
    int num_vertices;        // Número de vértices no grafo
} Grafo;

// Função para criar um grafo vazio
Grafo *criar(int num) { // num representa a quantidade máxima de vértices que pode ter no grafo
    Grafo *g = (Grafo *)malloc(sizeof(Grafo)); // Alocando espaço
    g->vertices = (NoAdjacencia **)malloc(num * sizeof(NoAdjacencia *));
    g->num_vertices = 0;
    return g;
}

// Função para adicionar livros no grafo
void adciona(Grafo *g, Livro *liv) {
    // Alocando espaço para um novo vértice
    NoAdjacencia *novo = (NoAdjacencia *)malloc(sizeof(NoAdjacencia));
    novo->livro = liv;
    novo->arestas = NULL;
    novo->num_arestas = 0;

    // Adicionando os vértices
    g->vertices[g->num_vertices] = novo;
    g->num_vertices++;
}

// Função para buscar um vértice no grafo
NoAdjacencia *buscar(Grafo *g, Livro *liv) {
    for (int i = 0; i < g->num_vertices; i++) {
        if (g->vertices[i]->livro->isbn == liv->isbn) {
            return g->vertices[i];
        }
    }
    return NULL;
}

// Função para criar uma relação entre dois livros
void adciona_rel(Grafo *g, Livro *liv1, Livro *liv2, int peso) {
    NoAdjacencia *n1 = buscar(g, liv1);
    NoAdjacencia *n2 = buscar(g, liv2);

    if (!n1 || !n2) {
        printf("Erro: Um dos livros não foi encontrado.\n");
        return;
    }

    // Adicionando a relação no vértice n1
    n1->arestas = (Aresta *)realloc(n1->arestas, (n1->num_arestas + 1) * sizeof(Aresta));
    n1->arestas[n1->num_arestas].destino = n2; // Aresta aponta para o vértice n2
    n1->arestas[n1->num_arestas].peso = peso;
    n1->num_arestas++;

    // Adicionando a relação no vértice n2 (grafo não-direcionado)
    n2->arestas = (Aresta *)realloc(n2->arestas, (n2->num_arestas + 1) * sizeof(Aresta));
    n2->arestas[n2->num_arestas].destino = n1; // Aresta aponta para o vértice n1
    n2->arestas[n2->num_arestas].peso = peso;
    n2->num_arestas++;
}

//Busca em Profundidade no grafo
void busca_em_profundidade(NoAdjacencia *vert, int *visitado){ //'vert' são vértices
int i;
if(visitado[vert->livro->isbn]) return;

printf("Visitando o livro de ISBN: %d\n", vert->livro->isbn);
visitado[vert->livro->isbn] = 1;

for(i = 0; i < vert->num_arestas; i++){
    busca_em_profundidade(vert->arestas[i].destino, visitado);
}

}

//Função para inciar a busca em profundidade 
void iniciar_busca_em_profundidade(Grafo * g, Livro *liv){

    int *visitado = (int *)calloc(10000, sizeof(int)); //Supondo ISBNs unicos menores que 10000
    NoAdjacencia *vertice = buscar(g, liv);

    if(vertice){
        busca_em_profundidade(vertice, visitado);
    }else{
        printf("Livro inicial não encontrado");
    }

    free(visitado);

}

//Função para busca em Largura

void busca_em_largura(Grafo *g, Livro *liv){
int front = 0, rear = 0, i;  

int *visitado = (int *)calloc(10000, sizeof(int)); //Supondo ISBNs unicos menores que 10000
    NoAdjacencia *inicio = buscar(g, liv);

    if(!inicio){
        printf("Livro inicial não encontrado.\n");
        free(visitado);
        return;
    }

    NoAdjacencia **fila = (NoAdjacencia **)malloc(g->num_vertices * sizeof(NoAdjacencia*));

    fila[rear++] = inicio;
    visitado[inicio->livro->isbn];

    while(front < rear){
        NoAdjacencia * atual = fila[front++];
        printf("Visitando o livro de ISBN: %d\n", atual->livro->isbn);

        for(i = 0; i < atual->num_arestas; i++){
            NoAdjacencia *adj = atual->arestas[i].destino;

            if(!visitado[adj->livro->isbn]){
                fila[rear++] = adj;
                visitado[adj->livro->isbn] = 1;
            }
        }
    }

    free(fila);
    free(visitado);

}

//Função para o algorítmo de Dijkstra com o caminho mais forte
void dijkstra(Grafo *g, Livro *inicio, Livro *fim){
    int i, j, k, peso;
    int *dist = (int*)malloc(g->num_vertices * sizeof(int));
    int *visitado = (int*)calloc(g->num_vertices, sizeof(int));
    NoAdjacencia **caminho = (NoAdjacencia**)malloc(g->num_vertices * sizeof(NoAdjacencia*));
    for(i = 0; i < g->num_vertices; i++){
        dist[i] = __INT_MAX__;

    }

    NoAdjacencia *inicio_vert = buscar(g, inicio);
    if(!inicio_vert){
        printf("Livro inicial nao encontado.\n");
        return;
    }

    dist[inicio_vert - g->vertices[0]] = 0; //A distância inicial é zero
    caminho[inicio_vert - g->vertices[0]] = NULL;

    for(i = 0; i < g->num_vertices; i++){
        NoAdjacencia *atual = NULL;
        int min_dist = __INT_MAX__; //Inicializa a distância mínima como infinito

        //Encontra a menor distância não visitada
        for(j = 0; j < g->num_vertices; j++){
            if(!visitado[j] && dist[j] < min_dist){
                atual = g->vertices[j];
                min_dist = dist[j];
            }
        }

        if(!atual) break; //Se não houver vértices a serem visitados interrompe

        for(k = 0; k < atual->num_arestas; k++){
            NoAdjacencia *adj = atual->arestas[k].destino;
            peso = atual->arestas[k].peso;

            if(dist[adj - g->vertices[0]] > dist[atual - g->vertices[0]] + peso){
                dist[adj - g->vertices[0]] = dist[atual - g->vertices[0]] + peso;
                caminho[adj - g->vertices[0]] = atual;
            }

        }
     }

     NoAdjacencia *fim_vert = buscar(g, fim);
     if(fim_vert){
        printf("O caminho mais forte ate o livro ISBN %d e de: %d\n", fim->isbn, dist[fim_vert - g->vertices[0]]);
     }else{
        printf("Livro final nao encontrado!\n");
     }

     free(dist);
     free(visitado);
     free(caminho);
}

//Função para sugerir livros
// Função para sugerir livros relacionados
void sugerir_livros(Grafo *g, Livro *livro) {
    NoAdjacencia *vertice = buscar(g, livro);
    if (vertice != NULL) {
        printf("Livros relacionados ao ISBN %d:\n", livro->isbn);
        for (int i = 0; i < vertice->num_arestas; i++) {
            printf("- %s (ISBN: %d)\n", vertice->arestas[i].destino->livro->titulo, vertice->arestas[i].destino->livro->isbn);
        }
    } else {
        printf("Livro com ISBN %d não encontrado!\n", livro->isbn);
    }
}
