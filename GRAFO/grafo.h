#ifndef GRAFO_H
#define GRAFO_H

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
    int peso;               // Peso da relação entre dois livros
    struct NoAdjacencia *destino;  // Ponteiro para o vértice relacionado
} Aresta;

// Estrutura de um nó na lista de adjacências
typedef struct NoAdjacencia {
    Livro *livro;        // Vértice que representa o livro
    Aresta *arestas;     // Lista de arestas para relações com outros livros
    int num_arestas;     // Número de arestas
} NoAdjacencia;

// Grafo de livros com lista de adjacências
typedef struct Grafo {
    NoAdjacencia **vertices;  // Lista de vértices
    int num_vertices;         // Número de vértices no grafo
} Grafo;

// Função para criar um grafo vazio
Grafo *criar(int num);  // num representa a quantidade máxima de vértices que pode ter no grafo

// Função para adicionar livros no grafo
void adciona(Grafo *g, Livro *liv); 

// Função para buscar um vértice no grafo
NoAdjacencia *buscar(Grafo *g, Livro *liv); 

// Função para criar uma relação entre dois livros
void adciona_rel(Grafo *g, Livro *liv1, Livro *liv2, int peso);

// Função para realizar busca em profundidade no grafo
void busca_em_profundidade(NoAdjacencia *vert, int *visitado);

// Função para iniciar a busca em profundidade
void iniciar_busca_em_profundidade(Grafo *g, Livro *liv);

// Função para realizar busca em largura no grafo
void busca_em_largura(Grafo *g, Livro *liv);

// Função para o algoritmo de Dijkstra com o caminho mais forte
void dijkstra(Grafo *g, Livro *inicio, Livro *fim);

void sugerir_livros(Grafo *g, Livro *livro);

#endif // GRAFO_H
