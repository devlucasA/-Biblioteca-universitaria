#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

//Função para trocar os elementos
void troca(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quickSort(int arr[], int menor, int maior) {
    if (menor < maior) {
        int pi = particiona(arr, menor, maior);
        quickSort(arr, menor, pi - 1);
        quickSort(arr, pi + 1, maior);
    }
}

//Função para particionar o array no quicksort
int particiona(int *arr, int menor, int maior) {
    int pivo = arr[maior]; //Escolhe o último elemento como pivô
    int i = menor - 1, j;

    for ( j = menor; j < maior; j++) {
        if (arr[j] < pivo) { //Se o elemento atual for menor que o pivô
            i++;
            troca(&arr[i], &arr[j]);
        }
    }
    troca(&arr[i + 1], &arr[maior]); //Troca a posição do pivô
    return i + 1; //Retorna o índice do pivô
}

//Função HeapSort
void heapSort(int *arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) // Constrói o Max-Heap
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        troca(&arr[0], &arr[i]); // Move o maior elemento para o final
        heapify(arr, i, 0); // Reconstroi o heap para os elementos restantes
    }
}

void heapify(int *arr, int n, int i) {
    int maior = i; // Inicializa o maior como raiz
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if (esquerda < n && arr[esquerda] > arr[maior]) // Verifica o filho esquerdo
        maior = esquerda;

    if (direita < n && arr[direita] > arr[maior]) // Verifica o filho direito
        maior = direita;

    if (maior != i) { // Se o maior não é a raiz
        troca(&arr[i], &arr[maior]);
        heapify(arr, n, maior); // Recursivamente aplica o heapify
    }
}


//Função MergeSort
void mergeSort(int *arr, int esquerda, int direita) {
    if (esquerda < direita) {
        int meio = esquerda + (direita - esquerda) / 2; // Calcula o meio do array
        mergeSort(arr, esquerda, meio); // Ordena a primeira metade
        mergeSort(arr, meio + 1, direita); // Ordena a segunda metade
        merge(arr, esquerda, meio, direita); // Junta as duas metades
    }
}

void merge(int *arr, int esquerda, int meio, int direita) {
    
    int n1 = meio - esquerda + 1;
    int n2 = direita - meio;

    int L[n1], R[n2]; // Arrays temporários para as duas metades

    for (int i = 0; i < n1; i++)
        L[i] = arr[esquerda + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[meio + 1 + j];

    int i = 0, j = 0, k = esquerda;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) { // Copia os elementos restantes de L
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) { // Copia os elementos restantes de R
        arr[k] = R[j];
        j++;
        k++;
    }
}


