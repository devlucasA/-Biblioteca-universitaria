#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

// Função para exibir o menu de opções
void menu() {
    printf("\n--- Menu de Grafo de Livros ---\n");
    printf("1. Inserir um livro\n");
    printf("2. Criar uma relação entre livros\n");
    printf("3. Buscar um livro\n");
    printf("4. Buscar livros relacionados (DFS)\n");
    printf("5. Buscar livros relacionados (BFS)\n");
    printf("6. Encontrar o caminho mais forte entre dois livros (Dijkstra)\n");
    printf("7. Sugerir livros relacionados\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

// Função para inserir um livro manualmente
Livro* inserir_livro() {
    Livro *livro = (Livro*)malloc(sizeof(Livro));

    printf("Digite o ISBN do livro: ");
    scanf("%d", &livro->isbn);
    getchar();  // Limpar o buffer do teclado
    printf("Digite o título do livro: ");
    fgets(livro->titulo, sizeof(livro->titulo), stdin);
    livro->titulo[strcspn(livro->titulo, "\n")] = 0;  // Remover o '\n' no final
    printf("Digite o autor do livro: ");
    fgets(livro->autor, sizeof(livro->autor), stdin);
    livro->autor[strcspn(livro->autor, "\n")] = 0;  // Remover o '\n' no final
    printf("Digite o ano de publicação: ");
    scanf("%d", &livro->ano_publicacao);
    printf("Digite a quantidade de exemplares: ");
    scanf("%d", &livro->quantidade);

    return livro;
}

// Função principal
int main() {
    Grafo *grafo = criar(100);  // Cria o grafo com capacidade para até 100 livros
    int opcao;
    Livro *livro1, *livro2;
    int isbn_busca, peso;

    do {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                livro1 = inserir_livro();
                adciona(grafo, livro1);
                printf("Livro '%s' inserido com sucesso!\n", livro1->titulo);
                break;

            case 2:
                printf("Digite o ISBN do primeiro livro: ");
                scanf("%d", &isbn_busca);
                livro1 = (Livro*)malloc(sizeof(Livro));
                livro1->isbn = isbn_busca;
                printf("Digite o ISBN do segundo livro: ");
                scanf("%d", &isbn_busca);
                livro2 = (Livro*)malloc(sizeof(Livro));
                livro2->isbn = isbn_busca;
                printf("Digite o peso da relação (1 a 5): ");
                scanf("%d", &peso);
                adciona_rel(grafo, livro1, livro2, peso);
                printf("Relação entre os livros criada com sucesso!\n");
                break;

            case 3:
                printf("Digite o ISBN do livro para buscar: ");
                scanf("%d", &isbn_busca);
                livro1 = (Livro*)malloc(sizeof(Livro));
                livro1->isbn = isbn_busca;
                NoAdjacencia *resultado = buscar(grafo, livro1);
                if (resultado != NULL)
                    printf("Livro '%s' encontrado!\n", resultado->livro->titulo);
                else
                    printf("Livro com ISBN %d não encontrado.\n", isbn_busca);
                break;

            case 4:
                printf("Digite o ISBN do livro para iniciar a busca em profundidade (DFS): ");
                scanf("%d", &isbn_busca);
                livro1 = (Livro*)malloc(sizeof(Livro));
                livro1->isbn = isbn_busca;
                iniciar_busca_em_profundidade(grafo, livro1);
                break;

            case 5:
                printf("Digite o ISBN do livro para iniciar a busca em largura (BFS): ");
                scanf("%d", &isbn_busca);
                livro1 = (Livro*)malloc(sizeof(Livro));
                livro1->isbn = isbn_busca;
                busca_em_largura(grafo, livro1);
                break;

            case 6:
                printf("Digite o ISBN do livro de início: ");
                scanf("%d", &isbn_busca);
                livro1 = (Livro*)malloc(sizeof(Livro));
                livro1->isbn = isbn_busca;
                printf("Digite o ISBN do livro de fim: ");
                scanf("%d", &isbn_busca);
                livro2 = (Livro*)malloc(sizeof(Livro));
                livro2->isbn = isbn_busca;
                dijkstra(grafo, livro1, livro2);
                break;

            case 7:
                printf("Digite o ISBN do livro para sugerir livros relacionados: ");
                scanf("%d", &isbn_busca);
                livro1 = (Livro*)malloc(sizeof(Livro));
                livro1->isbn = isbn_busca;
                sugerir_livros(grafo, livro1);
                break;

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    // Liberar a memória alocada para o grafo antes de sair
    free(grafo->vertices);
    free(grafo);

    return 0;
}
