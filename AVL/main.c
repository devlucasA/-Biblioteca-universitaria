
#include <stdio.h>
#include <stdlib.h>
#include "avl.h"


void menu() {
    printf("\n--- Menu AVL ---\n");
    printf("1. Inserir um elemento\n");
    printf("2. Remover um elemento\n");
    printf("3. Buscar um elemento\n");
    printf("4. Exibir em Pre-ordem\n");
    printf("5. Exibir em In-ordem\n");
    printf("6. Exibir em Pos-ordem\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    AVLTree* tree = createAVLTree();
    int option, key;

    do {
        menu();
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Digite o valor para inserir: ");
                scanf("%d", &key);
                tree->root = insertNode(tree->root, key);
                printf("Elemento %d inserido com sucesso!\n", key);
                break;

            case 2:
                printf("Digite o valor para remover: ");
                scanf("%d", &key);
                tree->root = deleteNode(tree->root, key);
                printf("Elemento %d removido (se existente).\n", key);
                break;

            case 3:
                printf("Digite o valor para buscar: ");
                scanf("%d", &key);
                Node* result = searchNode(tree->root, key);
                if (result != NULL)
                    printf("Elemento %d encontrado!\n", key);
                else
                    printf("Elemento %d nao encontrado.\n", key);
                break;

            case 4:
                printf("Exibindo em Pre-ordem: ");
                preOrder(tree->root);
                printf("\n");
                break;

            case 5:
                printf("Exibindo em In-ordem: ");
                inOrder(tree->root);
                printf("\n");
                break;

            case 6:
                printf("Exibindo em Pos-ordem: ");
                postOrder(tree->root);
                printf("\n");
                break;

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    } while (option != 0);

    // Liberar a memória da árvore antes de sair
    freeTree(tree->root);
    free(tree);

    return 0;
}
