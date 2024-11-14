#ifndef GRAFO_H
#define GRAFO_H

typedef struct Livro {
    int isbn;
    char titulo[100];
    char autor[100];
    int ano_publicacao;
    int quantidade;
} Livro;

typedef struct Aresta {
    struct NoAdjacencia *destino;  // Ponteiro para o vértice relacionado
    int peso;                      // Peso da relação
} Aresta;

typedef struct NoAdjacencia {
    Livro *livro;                  // Ponteiro para o livro
    Aresta *arestas;               // Lista de arestas (relacionamentos)
    int num_arestas;               // Número de arestas
} NoAdjacencia;

typedef struct Grafo {
    NoAdjacencia **vertices;       // Lista de vértices
    int num_vertices;              // Número de vértices no grafo
                   // Capacidade máxima de vértices
} Grafo;

// Declarações de funções
Grafo *criar(int num);
void adciona(Grafo *g, Livro *liv);
NoAdjacencia *buscar(Grafo *g, Livro *liv);
void adciona_rel(Grafo *g, Livro *liv1, Livro *liv2, int peso);
void busca_em_profundidade(NoAdjacencia *vert, int *visitado);
void iniciar_busca_em_profundidade(Grafo *g, Livro *liv);
void busca_em_largura(Grafo *g, Livro *liv);
void dijkstra(Grafo *g, Livro *inicio, Livro *fim);
void sugerir_livros(Grafo *g, Livro *livro);

#endif

