#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_JOGADORES 20

typedef struct {
    char nome[30];
    int pontuacao;
} Jogador;

typedef struct Node {
    Jogador jogador;
    struct Node *prox;
} Node;

// ======= VETOR =======
Jogador rankingVetor[MAX_JOGADORES];
int totalJogadores = 0;

// Insere mantendo ordem decrescente
void inserirVetor(char nome[], int pontuacao) {
    if (totalJogadores >= MAX_JOGADORES) {
        printf("⚠️  Ranking cheio!\n");
        return;
    }

    Jogador novo;
    strcpy(novo.nome, nome);
    novo.pontuacao = pontuacao;

    int i = totalJogadores - 1;
    while (i >= 0 && rankingVetor[i].pontuacao < pontuacao) {
        rankingVetor[i + 1] = rankingVetor[i];
        i--;
    }
    rankingVetor[i + 1] = novo;
    totalJogadores++;
    printf("✅ Jogador inserido!\n");
}

void removerVetor(char nome[]) {
    int i, j, encontrado = 0;
    for (i = 0; i < totalJogadores; i++) {
        if (strcmp(rankingVetor[i].nome, nome) == 0) {
            encontrado = 1;
            for (j = i; j < totalJogadores - 1; j++)
                rankingVetor[j] = rankingVetor[j + 1];
            totalJogadores--;
            printf("🗑️  Jogador removido!\n");
            break;
        }
    }
    if (!encontrado)
        printf("❌ Jogador não encontrado!\n");
}

void listarVetor() {
    printf("\n=== RANKING (VETOR) ===\n");
    for (int i = 0; i < totalJogadores; i++)
        printf("%dº %s - %d pts\n", i + 1, rankingVetor[i].nome, rankingVetor[i].pontuacao);
}

// Busca sequencial (linear)
int buscarSequencial(char nome[]) {
    for (int i = 0; i < totalJogadores; i++) {
        if (strcmp(rankingVetor[i].nome, nome) == 0)
            return i;
    }
    return -1;
}

// Busca binária iterativa
int buscarBinariaIterativa(char nome[]) {
    int inicio = 0, fim = totalJogadores - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(rankingVetor[meio].nome, nome);
        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

// Busca binária recursiva
int buscarBinariaRecursiva(char nome[], int inicio, int fim) {
    if (inicio > fim) return -1;
    int meio = (inicio + fim) / 2;
    int cmp = strcmp(rankingVetor[meio].nome, nome);
    if (cmp == 0)
        return meio;
    else if (cmp < 0)
        return buscarBinariaRecursiva(nome, meio + 1, fim);
    else
        return buscarBinariaRecursiva(nome, inicio, meio - 1);
}

// ======= LISTA ENCADEADA =======
Node *inicio = NULL;

void inserirLista(char nome[], int pontuacao) {
    Node *novo = malloc(sizeof(Node));
    strcpy(novo->jogador.nome, nome);
    novo->jogador.pontuacao = pontuacao;
    novo->prox = NULL;

    if (!inicio || pontuacao > inicio->jogador.pontuacao) {
        novo->prox = inicio;
        inicio = novo;
    } else {
        Node *atual = inicio;
        while (atual->prox && atual->prox->jogador.pontuacao >= pontuacao)
            atual = atual->prox;
        novo->prox = atual->prox;
        atual->prox = novo;
    }
}

void removerLista(char nome[]) {
    Node *atual = inicio, *ant = NULL;
    while (atual && strcmp(atual->jogador.nome, nome) != 0) {
        ant = atual;
        atual = atual->prox;
    }
    if (!atual) {
        printf("❌ Jogador não encontrado!\n");
        return;
    }
    if (!ant)
        inicio = atual->prox;
    else
        ant->prox = atual->prox;
    free(atual);
    printf("🗑️  Jogador removido (lista)!\n");
}

void listarLista() {
    printf("\n=== RANKING (LISTA) ===\n");
    Node *atual = inicio;
    int pos = 1;
    while (atual) {
        printf("%dº %s - %d pts\n", pos++, atual->jogador.nome, atual->jogador.pontuacao);
        atual = atual->prox;
    }
}

// ======= MAIN =======
int main() {
    int opcao;
    char nome[30];
    int pontuacao;

    do {
        printf("\n=== SISTEMA DE RANKING ===\n");
        printf("1. Inserir jogador\n");
        printf("2. Remover jogador\n");
        printf("3. Listar ranking\n");
        printf("4. Buscar jogador\n");
        printf("0. Sair\n> ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("Nome: ");
                fgets(nome, 30, stdin);
                nome[strcspn(nome, "\n")] = 0;
                printf("Pontuação: ");
                scanf("%d", &pontuacao);
                inserirVetor(nome, pontuacao);
                inserirLista(nome, pontuacao);
                break;

            case 2:
                printf("Nome: ");
                getchar();
                fgets(nome, 30, stdin);
                nome[strcspn(nome, "\n")] = 0;
                removerVetor(nome);
                removerLista(nome);
                break;

            case 3:
                listarVetor();
                listarLista();
                break;

            case 4:
                printf("Nome: ");
                getchar();
                fgets(nome, 30, stdin);
                nome[strcspn(nome, "\n")] = 0;
                printf("\n--- Busca Sequencial ---\n");
                int posSeq = buscarSequencial(nome);
                if (posSeq != -1)
                    printf("Encontrado na posição %d (vetor)\n", posSeq + 1);
                else
                    printf("Não encontrado!\n");

                printf("\n--- Busca Binária Iterativa ---\n");
                int posBin = buscarBinariaIterativa(nome);
                if (posBin != -1)
                    printf("Encontrado na posição %d (vetor)\n", posBin + 1);
                else
                    printf("Não encontrado!\n");

                printf("\n--- Busca Binária Recursiva ---\n");
                int posRec = buscarBinariaRecursiva(nome, 0, totalJogadores - 1);
                if (posRec != -1)
                    printf("Encontrado na posição %d (vetor)\n", posRec + 1);
                else
                    printf("Não encontrado!\n");
                break;

            case 0:
                printf("\nEncerrando o sistema...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}
