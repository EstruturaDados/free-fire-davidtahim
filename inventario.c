#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// Estrutura que representa um item da mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Vetor que armazenará até 10 itens
Item mochila[MAX_ITENS];
int totalItens = 0;

// Função para inserir um novo item na mochila
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("\n⚠️  Mochila cheia! Remova um item antes de adicionar outro.\n");
        return;
    }

    Item novo;
    printf("\n=== CADASTRO DE ITEM ===\n");
    printf("Nome do item: ");
    getchar(); // limpa o buffer
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = 0; // remove \n

    printf("Tipo (ex: arma, municao, cura): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila[totalItens++] = novo;
    printf("\n✅ Item adicionado com sucesso!\n");
}

// Função para remover item pelo nome
void removerItem() {
    if (totalItens == 0) {
        printf("\n⚠️  Mochila vazia!\n");
        return;
    }

    char nome[30];
    printf("\nNome do item a remover: ");
    getchar();
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    int encontrado = 0;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            totalItens--;
            encontrado = 1;
            printf("\n🗑️  Item '%s' removido com sucesso!\n", nome);
            break;
        }
    }

    if (!encontrado)
        printf("\n❌ Item nao encontrado!\n");
}

// Função para listar todos os itens
void listarItens() {
    printf("\n=== ITENS NA MOCHILA ===\n");
    if (totalItens == 0) {
        printf("A mochila está vazia.\n");
        return;
    }

    for (int i = 0; i < totalItens; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// Função de busca sequencial
void buscarItem() {
    if (totalItens == 0) {
        printf("\n⚠️  Mochila vazia!\n");
        return;
    }

    char nome[30];
    printf("\nNome do item a buscar: ");
    getchar();
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("\n🔍 Item encontrado!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }

    printf("\n❌ Item nao encontrado!\n");
}

int main() {
    int opcao;

    do {
        printf("\n=== SISTEMA DE INVENTÁRIO ===\n");
        printf("1. Cadastrar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inserirItem(); break;
            case 2: removerItem(); break;
            case 3: listarItens(); break;
            case 4: buscarItem(); break;
            case 0: printf("\nSaindo do inventário...\n"); break;
            default: printf("\nOpção inválida!\n");
        }

        listarItens(); // mostra sempre o inventário após cada ação
    } while (opcao != 0);

    return 0;
}
