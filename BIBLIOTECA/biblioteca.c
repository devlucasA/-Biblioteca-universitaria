#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"


Biblioteca* criarBiblioteca(int numLivros) {
    Biblioteca* biblioteca = (Biblioteca*)malloc(sizeof(Biblioteca));
    biblioteca->livrosPorISBN = createAVLTree();
    biblioteca->relacionamentos = createGraph(numLivros);
    return biblioteca;
}
/*
void destruirBiblioteca(Biblioteca* biblioteca) {
    freeAVLTree(biblioteca->livrosPorISBN);
    freeGraph(biblioteca->relacionamentos);
    free(biblioteca);
}
*/
void inserirLivro(Biblioteca* biblioteca, Livro livro) {
    Livro* novoLivro = (Livro*)malloc(sizeof(Livro));
    *novoLivro = livro; // Copia os dados do livro
    biblioteca->livrosPorISBN->root = insertNode(biblioteca->livrosPorISBN->root, livro.ISBN, novoLivro);
}

Livro* buscarLivroPorISBN(Biblioteca* biblioteca, int ISBN) {
    Node* node = searchNode(biblioteca->livrosPorISBN->root, ISBN);
    if (node != NULL && node->data != NULL) {
        return (Livro*)node->data; // Retorna o ponteiro para o livro
    }
    return NULL;
}//

void sugerirLivroPorRelacionamento(Biblioteca* biblioteca, int ISBN) {
    int index = ISBN % biblioteca->relacionamentos->numVertices;
    bfs(biblioteca->relacionamentos, index);
    // BFS pode listar livros relacionados ao ISBN dado.
}

void merge(Livro* livros, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Livro* leftArray = (Livro*)malloc(n1 * sizeof(Livro));
    Livro* rightArray = (Livro*)malloc(n2 * sizeof(Livro));

    for (int i = 0; i < n1; i++)
        leftArray[i] = livros[left + i];
    for (int i = 0; i < n2; i++)
        rightArray[i] = livros[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArray[i].ISBN <= rightArray[j].ISBN) {
            livros[k++] = leftArray[i++];
        } else {
            livros[k++] = rightArray[j++];
        }
    }

    while (i < n1) livros[k++] = leftArray[i++];
    while (j < n2) livros[k++] = rightArray[j++];

    free(leftArray);
    free(rightArray);
}

void mergeSort(Livro* livros, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(livros, left, mid);
        mergeSort(livros, mid + 1, right);
        merge(livros, left, mid, right);
    }
}

int partition(Livro* livros, int low, int high) {
    Livro pivot = livros[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (livros[j].ISBN < pivot.ISBN) {
            i++;
            Livro temp = livros[i];
            livros[i] = livros[j];
            livros[j] = temp;
        }
    }

    Livro temp = livros[i + 1];
    livros[i + 1] = livros[high];
    livros[high] = temp;

    return i + 1;
}

void quickSort(Livro* livros, int low, int high) {
    if (low < high) {
        int pi = partition(livros, low, high);
        quickSort(livros, low, pi - 1);
        quickSort(livros, pi + 1, high);
    }
}

void heapify(Livro* livros, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && livros[left].ISBN > livros[largest].ISBN)
        largest = left;

    if (right < n && livros[right].ISBN > livros[largest].ISBN)
        largest = right;

    if (largest != i) {
        Livro temp = livros[i];
        livros[i] = livros[largest];
        livros[largest] = temp;

        heapify(livros, n, largest);
    }
}

void heapSort(Livro* livros, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(livros, n, i);

    for (int i = n - 1; i > 0; i--) {
        Livro temp = livros[0];
        livros[0] = livros[i];
        livros[i] = temp;

        heapify(livros, i, 0);
    }
}








Livro* livrosOrdenados(Biblioteca* biblioteca, int* tamanho) {
    // Obtenha todos os livros da AVL em um array
    int numLivros = 0;
    Livro* livros = obterLivrosEmArray(biblioteca->livrosPorISBN, &numLivros);

    // Use o algoritmo mais eficiente de ordenação
    if (numLivros > 1000) {
        heapSort(livros, numLivros);
    } else if (numLivros > 100) {
        quickSort(livros, 0, numLivros - 1);
    } else {
        mergeSort(livros, 0, numLivros - 1);
    }

    *tamanho = numLivros;
    return livros;
}



int contarNos(Node* node) {
    if (node == NULL) {
        return 0;
    }
    // Conta o nó atual (1) + nós à esquerda e à direita
    return 1 + contarNos(node->left) + contarNos(node->right);
}

// Função recursiva para preencher um array com os livros da árvore AVL
void preencherArray(Node* node, Livro* livros, int* index) {
    if (node == NULL) 
        return;

    preencherArray(node->left, livros, index);

    if (node->data != NULL) {
        livros[*index] = *(Livro*)node->data; // Copia o livro para o array
        (*index)++;
    }

    preencherArray(node->right, livros, index);
}

// Obtem todos os livros em um array a partir da AVLTree
Livro* obterLivrosEmArray(AVLTree* tree, int* numLivros) {
    *numLivros = contarNos(tree->root);
    Livro* livros = (Livro*)malloc(*numLivros * sizeof(Livro));
    int index = 0;
    preencherArray(tree->root, livros, &index);
    return livros;
}
    // Contar o número de nós (livros) na AVL

