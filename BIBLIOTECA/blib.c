#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blib.h"

// Função para inicializar a biblioteca
Biblioteca* inicializaBiblioteca(int numVertices) {
    Biblioteca* biblioteca = (Biblioteca*)malloc(sizeof(Biblioteca));
    biblioteca->livrosAVL = createAVLTree();
    biblioteca->relacionamentos = createGraph(numVertices);
    return biblioteca;
}

// Função auxiliar para criar um livro (e adicioná-lo na AVL)
void adicionaLivro(Biblioteca* biblioteca, Livro livro) {
    Node* novoLivro = createNode(livro.id);
    strcpy((char*)novoLivro->key, livro.titulo);  // Associa o título ao nó
    biblioteca->livrosAVL->root = insertNode(biblioteca->livrosAVL->root, livro.id);
    printf("Livro '%s' adicionado.\n", livro.titulo);
}

// Remove um livro da biblioteca (e da AVL)
void removeLivro(Biblioteca* biblioteca, int livroId) {
    biblioteca->livrosAVL->root = deleteNode(biblioteca->livrosAVL->root, livroId);
    printf("Livro com ID %d removido.\n", livroId);
}

// Função para relacionar dois livros (ex: associar por tema ou autor)
void relacionaLivros(Biblioteca* biblioteca, int livroId1, int livroId2) {
    addEdge(biblioteca->relacionamentos, livroId1, livroId2, 1);  // Peso padrão 1
    printf("Relacionamento adicionado entre livro %d e livro %d.\n", livroId1, livroId2);
}

// Busca um livro pelo título na AVL
Livro* buscaLivroPorTitulo(Biblioteca* biblioteca, const char* titulo) {
    Node* node = searchNode(biblioteca->livrosAVL->root, (int)titulo);
    if (node != NULL) {
        printf("Livro encontrado: %s\n", titulo);
        return (Livro*)node->key;  // Converte para Livro
    }
    printf("Livro com título '%s' não encontrado.\n", titulo);
    return NULL;
}

// Sugere livros relacionados a partir de um livro específico usando BFS
void sugereLivros(Biblioteca* biblioteca, int livroId) {
    printf("Sugestões de livros para o livro com ID %d:\n", livroId);
    bfs(biblioteca->relacionamentos, livroId);
}

// Libera a memória da biblioteca
void liberaBiblioteca(Biblioteca* biblioteca) {
    freeTree(biblioteca->livrosAVL->root);
    freeGraph(biblioteca->relacionamentos);
    free(biblioteca);
    printf("Memória da biblioteca liberada.\n");
}
