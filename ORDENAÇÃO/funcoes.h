#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>

// Função para trocar os elementos
void troca(int *a, int *b);

// Funções para QuickSort
void quickSort(int arr[], int menor, int maior);
int particiona(int *arr, int menor, int maior);

// Funções para HeapSort
void heapSort(int *arr, int n);
void heapify(int *arr, int n, int i);

// Funções para MergeSort
void mergeSort(int *arr, int esquerda, int direita);
void merge(int *arr, int esquerda, int meio, int direita);

#endif // FUNCOES_H
