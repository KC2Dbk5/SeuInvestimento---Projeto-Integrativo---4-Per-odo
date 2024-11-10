#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct pedido {
    int id;
    int status;
};

struct pedido* pedidos = NULL;
int total_pedidos = 0;

void cria_pedido() {
    struct pedido novo_pedido;

    while (1) {
        printf("Digite o id do pedido: ");
        if (scanf("%d", &novo_pedido.id) != 1) {
            printf("Erro ao ler o id.\n");
            while (getchar() != '\n'); // Limpa o buffer
            continue;
        }

        printf("Digite o status do pedido (0 - finalizado, 1 - em andamento): ");
        if (scanf("%d", &novo_pedido.status) != 1 || novo_pedido.status < 0 || novo_pedido.status > 1) {
            printf("Erro ao ler o status.\n");
            while (getchar() != '\n'); // Limpa o buffer
            continue;
        }

        break;
    }

    // Aumenta o tamanho do vetor de pedidos
    total_pedidos++;
    pedidos = (struct pedido*) realloc(pedidos, total_pedidos * sizeof(struct pedido));
    if (pedidos == NULL) {
        printf("Erro de alocação de memória!\n");
        exit(1);
    }

    pedidos[total_pedidos - 1] = novo_pedido;
    printf("Pedido criado com sucesso!\n");
}

void remover_pedido() {
    if (total_pedidos == 0) {
        printf("Não há pedidos para remover.\n");
        return;
    }

    int id;
    printf("Digite o id do pedido a ser removido: ");
    scanf("%d", &id);

    int encontrado = 0;
    for (int i = 0; i < total_pedidos; i++) {
        if (pedidos[i].id == id) {
            encontrado = 1;
            for (int j = i; j < total_pedidos - 1; j++) {
                pedidos[j] = pedidos[j + 1];
            }
            total_pedidos--;
            pedidos = (struct pedido*) realloc(pedidos, total_pedidos * sizeof(struct pedido));
            printf("Pedido removido com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Pedido com id %d não encontrado.\n", id);
    }
}

void ver_pedidos_em_andamento() {
    if (total_pedidos == 0) {
        printf("Não há pedidos em andamento.\n");
        return;
    }

    printf("Pedidos em andamento:\n");
    for (int i = 0; i < total_pedidos; i++) {
        if (pedidos[i].status == 1) {
            printf("ID: %d\n", pedidos[i].id);
        }
    }
}

int menu() {
    int opcao;
    printf("\nBEM-VINDO AO SISTEMA DE GERÊNCIA E CONTROLE DE PEDIDOS\n");
    printf("1 - Criar um pedido e adicionar à fila\n");
    printf("2 - Remover um pedido\n");
    printf("3 - Ver pedidos em andamento\n");
    printf("0 - Fechar a execução do programa\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    return opcao;
}

int main() {
    setlocale (LC_ALL, "portuguese");

    int opcao;
    do {
        opcao = menu();
        switch (opcao) {
            case 1:
                cria_pedido();
                break;
            case 2:
                remover_pedido();
                break;
            case 3:
                ver_pedidos_em_andamento();
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    free(pedidos); // Libera a memória alocada
    return 0;
}