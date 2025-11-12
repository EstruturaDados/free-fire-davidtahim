#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10
#define TAM_NOME 50

typedef struct {
    char nome[TAM_NOME];
    int quantidade;
} Item;

// -------- LISTA ESTÁTICA (VETOR) --------
typedef struct {
    Item itens[MAX_ITENS];
    int tamanho;
} MochilaVetor;

// -------- LISTA ENCADEADA --------
typedef struct Node {
    Item item;
    struct Node *prox;
} Node;

typedef struct {
    Node *inicio;
} MochilaLista;

// ---------- FUNÇÕES VETOR ----------
void inicializarVetor(MochilaVetor *m) {
    m->tamanho = 0;
}

void inserirVetor(MochilaVetor *m, char nome[], int qtd) {
    if (m->tamanho >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }
    strcpy(m->itens[m->tamanho].nome, nome);
    m->itens[m->tamanho].quantidade = qtd;
    m->tamanho++;
}

void removerVetor(MochilaVetor *m, char nome[]) {
    int i, encontrado = 0;
    for (i = 0; i < m->tamanho; i++) {
        if (strcmp(m->itens[i].nome, nome) == 0) {
            encontrado = 1;
            break;
        }
    }
    if (encontrado) {
        for (; i < m->tamanho - 1; i++) {
            m->itens[i] = m->itens[i + 1];
        }
        m->tamanho--;
        printf("Item removido!\n");
    } else {
        printf("Item nao encontrado!\n");
    }
}

void listarVetor(MochilaVetor *m) {
    printf("\n--- Mochila (Vetor) ---\n");
    for (int i = 0; i < m->tamanho; i++) {
        printf("%s - %d\n", m->itens[i].nome, m->itens[i].quantidade);
    }
}

void buscarVetor(MochilaVetor *m, char nome[]) {
    for (int i = 0; i < m->tamanho; i++) {
        if (strcmp(m->itens[i].nome, nome) == 0) {
            printf("Item encontrado: %s - %d\n", m->itens[i].nome, m->itens[i].quantidade);
            return;
        }
    }
    printf("Item nao encontrado!\n");
}

// ---------- FUNÇÕES LISTA ENCADEADA ----------
void inicializarLista(MochilaLista *m) {
    m->inicio = NULL;
}

void inserirLista(MochilaLista *m, char nome[], int qtd) {
    Node *novo = (Node *)malloc(sizeof(Node));
    strcpy(novo->item.nome, nome);
    novo->item.quantidade = qtd;
    novo->prox = m->inicio;
    m->inicio = novo;
}

void removerLista(MochilaLista *m, char nome[]) {
    Node *atual = m->inicio, *anterior = NULL;
    while (atual != NULL && strcmp(atual->item.nome, nome) != 0) {
        anterior = atual;
        atual = atual->prox;
    }
    if (atual == NULL) {
        printf("Item nao encontrado!\n");
        return;
    }
    if (anterior == NULL)
        m->inicio = atual->prox;
    else
        anterior->prox = atual->prox;

    free(atual);
    printf("Item removido!\n");
}

void listarLista(MochilaLista *m) {
    printf("\n--- Mochila (Lista Encadeada) ---\n");
    Node *atual = m->inicio;
    while (atual != NULL) {
        printf("%s - %d\n", atual->item.nome, atual->item.quantidade);
        atual = atual->prox;
    }
}

void buscarLista(MochilaLista *m, char nome[]) {
    Node *atual = m->inicio;
    while (atual != NULL) {
        if (strcmp(atual->item.nome, nome) == 0) {
            printf("Item encontrado: %s - %d\n", atual->item.nome, atual->item.quantidade);
            return;
        }
        atual = atual->prox;
    }
    printf("Item nao encontrado!\n");
}

// ---------- MAIN ----------
int main() {
    MochilaVetor mochilaV;
    MochilaLista mochilaL;
    inicializarVetor(&mochilaV);
    inicializarLista(&mochilaL);

    int opcao;
    char nome[TAM_NOME];
    int qtd;

    do {
        printf("\n1. Inserir\n2. Remover\n3. Listar\n4. Buscar\n0. Sair\n> ");
        scanf("%d", &opcao);
        getchar(); // limpa buffer

        switch (opcao) {
            case 1:
                printf("Nome do item: ");
                fgets(nome, TAM_NOME, stdin);
                nome[strcspn(nome, "\n")] = 0;
                printf("Quantidade: ");
                scanf("%d", &qtd);
                inserirVetor(&mochilaV, nome, qtd);
                inserirLista(&mochilaL, nome, qtd);
                break;
            case 2:
                printf("Nome do item: ");
                fgets(nome, TAM_NOME, stdin);
                nome[strcspn(nome, "\n")] = 0;
                removerVetor(&mochilaV, nome);
                removerLista(&mochilaL, nome);
                break;
            case 3:
                listarVetor(&mochilaV);
                listarLista(&mochilaL);
                break;
            case 4:
                printf("Nome do item: ");
                fgets(nome, TAM_NOME, stdin);
                nome[strcspn(nome, "\n")] = 0;
                buscarVetor(&mochilaV, nome);
                buscarLista(&mochilaL, nome);
                break;
        }
    } while (opcao != 0);

    return 0;
}
