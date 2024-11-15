#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

void imprimeArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr_quick[] = {12, 11, 13, 5, 6, 7};
    int arr_heap[] = {12, 11, 13, 5, 6, 7};
    int arr_merge[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr_quick) / sizeof(arr_quick[0]);

    printf("Array original:\n");
    imprimeArray(arr_quick, n);

    // Testando QuickSort
    printf("\nOrdenando com QuickSort:\n");
    quickSort(arr_quick, 0, n - 1);
    imprimeArray(arr_quick, n);

    // Testando HeapSort
    printf("\nOrdenando com HeapSort:\n");
    heapSort(arr_heap, n);
    imprimeArray(arr_heap, n);

    // Testando MergeSort
    printf("\nOrdenando com MergeSort:\n");
    mergeSort(arr_merge, 0, n - 1);
    imprimeArray(arr_merge, n);

    return 0;
}
