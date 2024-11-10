#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

struct produto {
    int id;
    char nome[50];
    float valor;
    struct produto *prox;
    struct produto *ant;
};

typedef struct produto Produto;

typedef struct {
    Produto *inicio;
} Estoque;

// função para imprimir o estoque
void imprimir_estoque(Estoque *e) {
    Produto *aux;
    aux = e->inicio;

    if (aux == NULL) {
        printf("ESTOQUE VAZIO\n");
    } else {
        printf("\nPRODUTOS NO ESTOQUE:\n");
        while (aux != NULL) {
            printf("ID: %d | Nome: %s | Valor: %.2f\n", aux->id, aux->nome, aux->valor);
            aux = aux->prox;
        }
    }
}

// buscar um produto usando o ID
void buscar_produto(Estoque *e) {
    Produto *aux;
    aux = e->inicio;
    int id_buscado, encontrou = 0;

    printf("Digite o ID do produto buscado: ");
    scanf("%d", &id_buscado);

    if (aux == NULL) {
        printf("\nEstoque vazio - Produto não encontrado\n");
    } else {
        while (aux != NULL) {
            if (id_buscado == aux->id) {
                printf("Produto encontrado: Nome: %s | Valor: %.2f\n", aux->nome, aux->valor);
                encontrou = 1;
                break;
            }
            aux = aux->prox;
        }
        if (encontrou == 0) {
            printf("Produto não encontrado no estoque\n");
        }
    }
}

// inserir um novo produto no estoque
void inserir_produto(Estoque *e) {
    Produto *aux, *novo_produto;
    int novo_id;
    char novo_nome[50];
    float novo_valor;

    aux = e->inicio;
    printf("Digite o ID do produto: ");
    scanf("%d", &novo_id);
    printf("Digite o nome do produto: ");
    scanf(" %[^\n]s", novo_nome); // lê o nome com espaços
    printf("Digite o valor do produto: ");
    scanf("%f", &novo_valor);

    // aloca memória para o novo produto e configura seus valores utilizando da função struct
    novo_produto = malloc(sizeof(Produto));
    novo_produto->id = novo_id;
    strcpy(novo_produto->nome, novo_nome);
    novo_produto->valor = novo_valor;
    novo_produto->prox = NULL;
    novo_produto->ant = NULL;

    // insere o novo produto
    if (aux == NULL) { // estoque vazio
        e->inicio = novo_produto;
    } else { // estoque não vazio
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novo_produto;
        novo_produto->ant = aux; // altera o ponteiro para o nó anterior
    }
}

// remover um produto do estoque usando o ID
void remover_produto(Estoque *e) {
    Produto *aux;
    int encontrou = 0;
    aux = e->inicio;

    if (aux == NULL) {
        printf("\nESTOQUE VAZIO\n");
    } else {
        int id_remover;
        printf("\nDigite o ID do produto a ser removido: ");
        scanf("%d", &id_remover);

        while (aux != NULL) {
            if (id_remover == aux->id) {
                encontrou = 1;
                if (aux == e->inicio) { // primeiro produto/cabeça da lista
                    e->inicio = aux->prox;
                    if (aux->prox != NULL) {
                        aux->prox->ant = NULL; // atualiza o ponteiro ant do próximo nó
                    }
                } else {
                    aux->ant->prox = aux->prox;
                    if (aux->prox != NULL) {
                        aux->prox->ant = aux->ant; // atualiza o ponteiro ant do próximo nó
                    }
                }
                free(aux);
                printf("Produto removido com sucesso!\n");
                break;
            }
            aux = aux->prox;
        }
        if (encontrou == 0) {
            printf("Produto não encontrado no estoque\n");
        }
    }
}

// altera o produto
void alterar_produto(Estoque *e) {
    Produto *aux;
    aux = e->inicio;
    int id_alterar, encontrou = 0;
    char novo_nome[50];
    float novo_valor;

    printf("Digite o ID do produto a ser alterado: ");
    scanf("%d", &id_alterar);

    if (aux == NULL) {
        printf("\nEstoque vazio - Produto não encontrado\n");
    } else {
        while (aux != NULL) {
            if (id_alterar == aux->id) {
                printf("Produto encontrado: Nome: %s | Valor: %.2f\n", aux->nome, aux->valor);
                printf("Digite o novo nome do produto: ");
                scanf(" %[^\n]s", novo_nome);
                printf("Digite o novo valor do produto: ");
                scanf("%f", &novo_valor);

                // atualiza o produto
                strcpy(aux->nome, novo_nome);
                aux->valor = novo_valor;
                printf("Produto alterado com sucesso!\n");
                encontrou = 1;
                break;
            }
            aux = aux->prox;
        }
        if (encontrou == 0) {
            printf("Produto não encontrado no estoque\n");
        }
    }
}

// função main com o menu
int main() {
    setlocale(LC_ALL, "portuguese");
    Estoque e;
    e.inicio = NULL;
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1 - Adicionar produto\n");
        printf("2 - Remover produto\n");
        printf("3 - Buscar produto\n");
        printf("4 - Alterar produto\n");
        printf("5 - Imprimir estoque\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                inserir_produto(&e);
                break;
            case 2:
                remover_produto(&e);
                break;
            case 3:
                buscar_produto(&e);
                break;
            case 4:
                alterar_produto(&e);
                break;
            case 5:
                imprimir_estoque(&e);
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida, tente novamente.\n");
        }
    } while(opcao != 0);

    return 0;
}