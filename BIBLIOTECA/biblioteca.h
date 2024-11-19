#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include "avl.h"
#include "grafo.h"
//#include "ordenacao.h"

// Estrutura de dados do Livro
typedef struct {
    int ISBN;
    char titulo[100];
    char autor[50];
    int anoPublicacao;
} Livro;

// Estrutura da Biblioteca
typedef struct {
    AVLTree* livrosPorISBN;
    Graph* relacionamentos;
} Biblioteca;

// Funções da biblioteca
Biblioteca* criarBiblioteca(int numLivros);
//void destruirBiblioteca(Biblioteca* biblioteca);
void inserirLivro(Biblioteca* biblioteca, Livro livro);
Livro* buscarLivroPorISBN(Biblioteca* biblioteca, int ISBN);
void sugerirLivroPorRelacionamento(Biblioteca* biblioteca, int ISBN);
Livro* livrosOrdenados(Biblioteca* biblioteca, int* tamanho);
Livro* obterLivrosEmArray(AVLTree* tree, int* numLivros);

#endif //BIBLIOTECA_H
