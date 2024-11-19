#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int ISBN;
    char titulo[100];
    char autor[100];
} Livro;

void quickSort(Livro arr[], int menor, int maior);
void heapSort(Livro *arr, int n);
void mergeSort(Livro *arr, int esquerda, int direita);
void troca(int *a, int *b);
int particiona(int *arr, int menor, int maior);
void heapify(int *arr, int n, int i);
void merge(int *arr, int esquerda, int meio, int direita);

#endif // FUNCOES_H
