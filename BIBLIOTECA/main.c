#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blib.h"

void menu() {
    printf("\n===== Biblioteca Menu =====\n");
    printf("1. Adicionar Livro\n");
    printf("2. Remover Livro\n");
    printf("3. Buscar Livro por Título\n");
    printf("4. Relacionar Livros\n");
    printf("5. Sugerir Livros Relacionados\n");
    printf("6. Exibir Livros (In-ordem)\n");
    printf("7. Sair\n");
    printf("===========================\n");
    printf("Escolha uma opção: ");
}

int main() {
    Biblioteca* biblioteca = inicializaBiblioteca(100); // Inicializa biblioteca com 100 vértices no grafo (ajuste conforme necessário)
    int opcao, id1, id2;
    char titulo[100], autor[100];

    while (1) {
        menu();
        scanf("%d", &opcao);
        getchar();  // Limpar o buffer após leitura de números

        switch (opcao) {
            case 1:
                printf("Digite o ID do livro: ");
                scanf("%d", &id1);
                getchar();
                
                printf("Digite o título do livro: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = '\0'; // Remove o newline
                
                printf("Digite o autor do livro: ");
                fgets(autor, sizeof(autor), stdin);
                autor[strcspn(autor, "\n")] = '\0'; // Remove o newline
                
                Livro livro;
                livro.id = id1;
                strcpy(livro.titulo, titulo);
                strcpy(livro.autor, autor);

                adicionaLivro(biblioteca, livro);
                break;
                
            case 2:
                printf("Digite o ID do livro a ser removido: ");
                scanf("%d", &id1);
                removeLivro(biblioteca, id1);
                break;
                
            case 3:
                printf("Digite o título do livro a ser buscado: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = '\0'; // Remove o newline
                buscaLivroPorTitulo(biblioteca, titulo);
                break;
                
            case 4:
                printf("Digite o ID do primeiro livro: ");
                scanf("%d", &id1);
                printf("Digite o ID do segundo livro: ");
                scanf("%d", &id2);
                relacionaLivros(biblioteca, id1, id2);
                break;
                
            case 5:
                printf("Digite o ID do livro para sugestões de relacionados: ");
                scanf("%d", &id1);
                sugereLivros(biblioteca, id1);
                break;
                
            case 6:
                printf("Livros na biblioteca (In-ordem): ");
                inOrder(biblioteca->livrosAVL->root);
                printf("\n");
                break;
                
            case 7:
                liberaBiblioteca(biblioteca);
                printf("Saindo do programa...\n");
                return 0;
                
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }
}
