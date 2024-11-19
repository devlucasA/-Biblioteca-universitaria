
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "biblioteca.h"

void menu() {
    printf("\n========== MENU BIBLIOTECA ==========\n");
    printf("1. Adicionar livro\n");
    printf("2. Buscar livro por ISBN\n");
    printf("3. Listar livros ordenados\n");
    printf("4. Sugerir livros relacionados\n");
    printf("5. Sair\n");
    printf("=====================================\n");
    printf("Escolha uma opcao: ");
}

void printLivro(Livro livro) {
    printf("\n--- Detalhes do Livro ---\n");
    printf("ISBN: %d\n", livro.ISBN);
    printf("Titulo: %s\n", livro.titulo);
    printf("Autor: %s\n", livro.autor);
    printf("Ano de Publicacao: %d\n", livro.anoPublicacao);
    printf("-------------------------\n");
}

int main() {
    Biblioteca* biblioteca = criarBiblioteca(100); // Inicializa com capacidade para 100 livros
    int opcao;

    do {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Livro novoLivro;
                printf("\nDigite o ISBN do livro: ");
                scanf("%d", &novoLivro.ISBN);
                printf("Digite o titulo do livro: ");
                getchar(); // Consumir o '\n' restante
                fgets(novoLivro.titulo, sizeof(novoLivro.titulo), stdin);
                strtok(novoLivro.titulo, "\n"); // Remover o '\n' do final
                printf("Digite o autor do livro: ");
                fgets(novoLivro.autor, sizeof(novoLivro.autor), stdin);
                strtok(novoLivro.autor, "\n");
                printf("Digite o ano de publicacao: ");
                scanf("%d", &novoLivro.anoPublicacao);

                inserirLivro(biblioteca, novoLivro);
                printf("\nLivro adicionado com sucesso!\n");
                break;
            }
            case 2: {
                int ISBN;
                printf("\nDigite o ISBN do livro que deseja buscar: ");
                scanf("%d", &ISBN);

                Livro* livro = buscarLivroPorISBN(biblioteca, ISBN);
                if (livro != NULL) {
                    printLivro(*livro);
                } else {
                    printf("\nLivro nao encontrado!\n");
                }
                break;
            }
            case 3: {
                int tamanho;
                Livro* livros = livrosOrdenados(biblioteca, &tamanho);
                if (tamanho > 0) {
                    printf("\nLivros ordenados:\n");
                    for (int i = 0; i < tamanho; i++) {
                        printLivro(livros[i]);
                    }
                    free(livros);
                } else {
                    printf("\nNao ha livros cadastrados.\n");
                }
                break;
            }
            case 4: {
                int ISBN;
                printf("\nDigite o ISBN do livro para sugestoes: ");
                scanf("%d", &ISBN);
                sugerirLivroPorRelacionamento(biblioteca, ISBN);
                break;
            }
            case 5:
                printf("\nSaindo do programa...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 5);

    // Libera memória da biblioteca antes de encerrar
    // destruirBiblioteca(biblioteca);
    return 0;
}
