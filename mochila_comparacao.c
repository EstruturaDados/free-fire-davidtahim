#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 10

// =============================
// ESTRUTURAS DE DADOS
// =============================
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No *proximo;
} No;

// =============================
// VARIÁVEIS GLOBAIS
// =============================
Item mochilaVetor[MAX_ITENS];
int totalItens = 0;

No *inicio = NULL;

int compSeq = 0;
int compBin = 0;

// =============================
// FUNÇÕES - VETOR
// =============================
void inserirItemVetor() {
    if (totalItens >= MAX_ITENS) {
        printf("\n⚠️  Mochila cheia!\n");
        return;
    }

    Item novo;
    printf("\n=== INSERIR ITEM (VETOR) ===\n");
    getchar();
    printf("Nome: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = 0;

    printf("Tipo: ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochilaVetor[totalItens++] = novo;
    printf("✅ Item adicionado com sucesso!\n");
}

void removerItemVetor() {
    if (totalItens == 0) {
        printf("\n⚠️  Mochila vazia!\n");
        return;
    }

    char nome[30];
    getchar();
    printf("\nNome do item a remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            for (int j = i; j < totalItens - 1; j++) {
                mochilaVetor[j] = mochilaVetor[j + 1];
            }
            totalItens--;
            printf("🗑️  Item removido com sucesso!\n");
            return;
        }
    }

    printf("❌ Item não encontrado!\n");
}

void listarItensVetor() {
    printf("\n=== ITENS NA MOCHILA (VETOR) ===\n");
    if (totalItens == 0) {
        printf("Mochila vazia.\n");
        return;
    }
    for (int i = 0; i < totalItens; i++) {
        printf("%d. %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
}

void ordenarVetor() {
    for (int i = 0; i < totalItens - 1; i++) {
        for (int j = 0; j < totalItens - i - 1; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }
    printf("\n📚 Vetor ordenado por nome!\n");
}

int buscarSequencialVetor(char nome[]) {
    compSeq = 0;
    for (int i = 0; i < totalItens; i++) {
        compSeq++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0)
            return i;
    }
    return -1;
}

int buscarBinariaVetor(char nome[]) {
    compBin = 0;
    int inicio = 0, fim = totalItens - 1;
    while (inicio <= fim) {
        compBin++;
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(mochilaVetor[meio].nome, nome);
        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

// =============================
// FUNÇÕES - LISTA ENCADEADA
// =============================
void inserirItemLista() {
    No *novo = malloc(sizeof(No));
    getchar();
    printf("\n=== INSERIR ITEM (LISTA) ===\n");
    printf("Nome: ");
    fgets(novo->dados.nome, sizeof(novo->dados.nome), stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = 0;

    printf("Tipo: ");
    fgets(novo->dados.tipo, sizeof(novo->dados.tipo), stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = inicio;
    inicio = novo;

    printf("✅ Item adicionado à lista!\n");
}

void removerItemLista() {
    if (!inicio) {
        printf("\n⚠️  Lista vazia!\n");
        return;
    }

    char nome[30];
    getchar();
    printf("\nNome do item a remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    No *atual = inicio, *anterior = NULL;

    while (atual && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (!atual) {
        printf("❌ Item não encontrado!\n");
        return;
    }

    if (!anterior)
        inicio = atual->proximo;
    else
        anterior->proximo = atual->proximo;

    free(atual);
    printf("🗑️  Item removido da lista!\n");
}

void listarItensLista() {
    printf("\n=== ITENS NA MOCHILA (LISTA ENCADEADA) ===\n");
    if (!inicio) {
        printf("Lista vazia.\n");
        return;
    }

    No *atual = inicio;
    int i = 1;
    while (atual) {
        printf("%d. %s | Tipo: %s | Quantidade: %d\n",
               i++, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

int buscarSequencialLista(char nome[]) {
    compSeq = 0;
    No *atual = inicio;
    while (atual) {
        compSeq++;
        if (strcmp(atual->dados.nome, nome) == 0)
            return 1;
        atual = atual->proximo;
    }
    return 0;
}

// =============================
// FUNÇÃO PRINCIPAL (MENU)
// =============================
int main() {
    int estrutura, opcao;
    char nome[30];
    clock_t inicioTempo, fimTempo;
    double tempo;

    do {
        printf("\n=== SISTEMA DE MOCHILA ===\n");
        printf("1. Usar Mochila (Vetor)\n");
        printf("2. Usar Mochila (Lista Encadeada)\n");
        printf("0. Sair\n> ");
        scanf("%d", &estrutura);

        switch (estrutura) {
            // --------------------- VETOR ---------------------
            case 1:
                do {
                    printf("\n--- Mochila com Vetor ---\n");
                    printf("1. Inserir item\n");
                    printf("2. Remover item\n");
                    printf("3. Listar itens\n");
                    printf("4. Ordenar vetor\n");
                    printf("5. Buscar item (sequencial)\n");
                    printf("6. Buscar item (binária)\n");
                    printf("0. Voltar\n> ");
                    scanf("%d", &opcao);

                    switch (opcao) {
                        case 1:
                            inserirItemVetor();
                            break;
                        case 2:
                            removerItemVetor();
                            break;
                        case 3:
                            listarItensVetor();
                            break;
                        case 4:
                            ordenarVetor();
                            break;
                        case 5:
                            getchar();
                            printf("Nome do item a buscar: ");
                            fgets(nome, sizeof(nome), stdin);
                            nome[strcspn(nome, "\n")] = 0;
                            inicioTempo = clock();
                            int pos = buscarSequencialVetor(nome);
                            fimTempo = clock();
                            tempo = ((double)(fimTempo - inicioTempo)) / CLOCKS_PER_SEC;
                            if (pos != -1)
                                printf("🔍 Encontrado na posição %d\n", pos + 1);
                            else
                                printf("❌ Item não encontrado!\n");
                            printf("Comparações: %d | Tempo: %.5fs\n", compSeq, tempo);
                            break;
                        case 6:
                            getchar();
                            printf("Nome do item a buscar (binária): ");
                            fgets(nome, sizeof(nome), stdin);
                            nome[strcspn(nome, "\n")] = 0;
                            inicioTempo = clock();
                            int posB = buscarBinariaVetor(nome);
                            fimTempo = clock();
                            tempo = ((double)(fimTempo - inicioTempo)) / CLOCKS_PER_SEC;
                            if (posB != -1)
                                printf("🔍 Encontrado na posição %d\n", posB + 1);
                            else
                                printf("❌ Item não encontrado!\n");
                            printf("Comparações: %d | Tempo: %.5fs\n", compBin, tempo);
                            break;
                    }
                } while (opcao != 0);
                break;

            // --------------------- LISTA ---------------------
            case 2:
                do {
                    printf("\n--- Mochila com Lista Encadeada ---\n");
                    printf("1. Inserir item\n");
                    printf("2. Remover item\n");
                    printf("3. Listar itens\n");
                    printf("4. Buscar item (sequencial)\n");
                    printf("0. Voltar\n> ");
                    scanf("%d", &opcao);

                    switch (opcao) {
                        case 1:
                            inserirItemLista();
                            break;
                        case 2:
                            removerItemLista();
                            break;
                        case 3:
                            listarItensLista();
                            break;
                        case 4:
                            getchar();
                            printf("Nome do item a buscar: ");
                            fgets(nome, sizeof(nome), stdin);
                            nome[strcspn(nome, "\n")] = 0;
                            inicioTempo = clock();
                            int encontrado = buscarSequencialLista(nome);
                            fimTempo = clock();
                            tempo = ((double)(fimTempo - inicioTempo)) / CLOCKS_PER_SEC;
                            if (encontrado)
                                printf("🔍 Item encontrado!\n");
                            else
                                printf("❌ Item não encontrado!\n");
                            printf("Comparações: %d | Tempo: %.5fs\n", compSeq, tempo);
                            break;
                    }
                } while (opcao != 0);
                break;

            case 0:
                printf("\nEncerrando o programa...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while (estrutura != 0);

    return 0;
}
