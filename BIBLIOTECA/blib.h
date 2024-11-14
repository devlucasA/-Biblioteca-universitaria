#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include "avl.h"
#include "grafo.h"

// Estrutura para um Livro
typedef struct Livro {
    int id;            // ID único para o livro
    char titulo[100];  // Título do livro
    char autor[100];   // Nome do autor
} Livro;

// Estrutura para um Autor
typedef struct Autor {
    int id;              // ID único para o autor
    char nome[100];      // Nome do autor
} Autor;

// Estrutura para a Biblioteca
typedef struct Biblioteca {
    AVLTree* livrosAVL;       // AVL para armazenar livros ordenados pelo título
    Graph* relacionamentos;   // Grafo para relacionar livros/autores
} Biblioteca;

// Funções para manipulação da Biblioteca

// Inicializa a biblioteca
Biblioteca* inicializaBiblioteca(int numVertices);

// Adiciona um livro à biblioteca
void adicionaLivro(Biblioteca* biblioteca, Livro livro);

// Remove um livro da biblioteca
void removeLivro(Biblioteca* biblioteca, int livroId);

// Relaciona dois livros (ex: de um mesmo autor)
void relacionaLivros(Biblioteca* biblioteca, int livroId1, int livroId2);

// Busca um livro pelo título
Livro* buscaLivroPorTitulo(Biblioteca* biblioteca, const char* titulo);

// Sugere livros relacionados a partir de um livro específico
void sugereLivros(Biblioteca* biblioteca, int livroId);

// Libera a memória da biblioteca
void liberaBiblioteca(Biblioteca* biblioteca);

#endif // BIBLIOTECA_H
