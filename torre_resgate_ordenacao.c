#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMP 20

// =========================
// ESTRUTURAS E ASSINATURAS
// =========================
typedef struct {
    char nome[30];
    char tipo[20];
    int  prioridade; // 1 (alta) a 10 (baixa) — ou conforme o jogo definir
} Componente;

// Para padronizar medição de tempo, os sorts seguem a mesma assinatura
typedef void (*SortFn)(Componente v[], int n, long *comparacoes, long *trocas);

// =========================
// UTILITÁRIOS
// =========================
static void lerLinha(char *buf, size_t tam) {
    if (fgets(buf, (int)tam, stdin)) {
        buf[strcspn(buf, "\n")] = 0;
    }
}

static void mostrarComponentes(Componente v[], int n) {
    printf("\n=== COMPONENTES ===\n");
    if (n == 0) {
        printf("(vazio)\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        printf("%2d) Nome: %-20s | Tipo: %-12s | Prioridade: %d\n",
               i + 1, v[i].nome, v[i].tipo, v[i].prioridade);
    }
}

// =========================
// ORDENAÇÃO
// =========================
// 1) Bubble sort por NOME (string)
void bubbleSortNome(Componente v[], int n, long *comparacoes, long *trocas) {
    *comparacoes = 0;
    *trocas = 0;
    for (int i = 0; i < n - 1; i++) {
        int houveTroca = 0;
        for (int j = 0; j < n - i - 1; j++) {
            (*comparacoes)++; // compara nomes
            if (strcmp(v[j].nome, v[j + 1].nome) > 0) {
                Componente tmp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = tmp;
                (*trocas)++;
                houveTroca = 1;
            }
        }
        if (!houveTroca) break; // melhor caso O(n)
    }
}

// 2) Insertion sort por TIPO (string)
void insertionSortTipo(Componente v[], int n, long *comparacoes, long *trocas) {
    *comparacoes = 0;
    *trocas = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = v[i];
        int j = i - 1;
        // enquanto v[j].tipo > chave.tipo, desloca
        while (j >= 0) {
            (*comparacoes)++;
            if (strcmp(v[j].tipo, chave.tipo) > 0) {
                v[j + 1] = v[j];
                (*trocas)++; // conta deslocamento como troca/movimento
                j--;
            } else {
                break;
            }
        }
        v[j + 1] = chave;
        // (não contamos aqui como troca adicional, já contamos deslocamentos)
    }
}

// 3) Selection sort por PRIORIDADE (int)
void selectionSortPrioridade(Componente v[], int n, long *comparacoes, long *trocas) {
    *comparacoes = 0;
    *trocas = 0;
    for (int i = 0; i < n - 1; i++) {
        int idxMin = i; // menor prioridade (1 é mais alta)
        for (int j = i + 1; j < n; j++) {
            (*comparacoes)++;
            if (v[j].prioridade < v[idxMin].prioridade) {
                idxMin = j;
            }
        }
        if (idxMin != i) {
            Componente tmp = v[i];
            v[i] = v[idxMin];
            v[idxMin] = tmp;
            (*trocas)++;
        }
    }
}

// =========================
// BUSCA BINÁRIA POR NOME
// (requer vetor ORDENADO POR NOME)
// =========================
int buscaBinariaPorNome(Componente v[], int n, const char alvo[], long *comparacoes) {
    int ini = 0, fim = n - 1;
    *comparacoes = 0;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(v[meio].nome, alvo);
        if (cmp == 0) return meio;
        if (cmp < 0) ini = meio + 1;
        else         fim = meio - 1;
    }
    return -1;
}

// =========================
// MEDIÇÃO DE TEMPO (SORT)
// =========================
double medirTempoSort(SortFn algoritmo, Componente v[], int n, long *comparacoes, long *trocas) {
    clock_t t0 = clock();
    algoritmo(v, n, comparacoes, trocas);
    clock_t t1 = clock();
    return (double)(t1 - t0) / CLOCKS_PER_SEC;
}

// =========================
// ENTRADA DE DADOS
// =========================
int cadastrarComponentes(Componente v[], int capacidade) {
    int n;
    printf("\nQuantos componentes deseja cadastrar? (1..%d): ", capacidade);
    scanf("%d", &n);
    getchar(); // consome \n
    if (n < 1) n = 1;
    if (n > capacidade) n = capacidade;

    for (int i = 0; i < n; i++) {
        printf("\n--- Componente %d ---\n", i + 1);
        printf("Nome (ex: chip central): ");
        lerLinha(v[i].nome, sizeof(v[i].nome));
        printf("Tipo (ex: controle/suporte/propulsao): ");
        lerLinha(v[i].tipo, sizeof(v[i].tipo));
        printf("Prioridade (1..10): ");
        scanf("%d", &v[i].prioridade);
        getchar();
        if (v[i].prioridade < 1) v[i].prioridade = 1;
        if (v[i].prioridade > 10) v[i].prioridade = 10;
    }
    return n;
}

// =========================
// MAIN (MENU INTERATIVO)
// =========================
int main(void) {
    Componente base[MAX_COMP];
    Componente trabalho[MAX_COMP]; // cópia para ordenar sem perder o original
    int n = 0;

    int temDados = 0;
    int ultimoOrdenadoPorNome = 0; // habilita busca binária
    long comp, trocas;

    while (1) {
        printf("\n========== TORRE DE RESGATE: MÓDULO AVANÇADO ==========\n");
        printf("1) Cadastrar/recadastrar componentes\n");
        printf("2) Mostrar componentes atuais\n");
        printf("3) Ordenar por NOME (Bubble)\n");
        printf("4) Ordenar por TIPO (Insertion)\n");
        printf("5) Ordenar por PRIORIDADE (Selection)\n");
        printf("6) Busca binária por NOME (requer ordenação por NOME)\n");
        printf("0) Sair\n> ");

        int op;
        if (scanf("%d", &op) != 1) { // entrada inválida
            return 0;
        }
        getchar(); // consome \n

        if (op == 0) {
            printf("\nEncerrando… boa sorte na fuga! 🛡️🚀\n");
            break;
        }

        switch (op) {
            case 1: {
                n = cadastrarComponentes(base, MAX_COMP);
                temDados = 1;
                ultimoOrdenadoPorNome = 0;
                printf("\n✅ Componentes cadastrados!\n");
            } break;

            case 2: {
                if (!temDados) { printf("\n⚠️ Cadastre primeiro.\n"); break; }
                mostrarComponentes(base, n);
            } break;

            case 3: { // Bubble por nome
                if (!temDados) { printf("\n⚠️ Cadastre primeiro.\n"); break; }
                memcpy(trabalho, base, sizeof(Componente) * n);
                double tempo = medirTempoSort(bubbleSortNome, trabalho, n, &comp, &trocas);
                mostrarComponentes(trabalho, n);
                printf("\n🫧 Bubble (por nome) → Comparações: %ld | Trocas: %ld | Tempo: %.6fs\n",
                       comp, trocas, tempo);
                // Atualiza “base” se quiser manter o estado ordenado
                memcpy(base, trabalho, sizeof(Componente) * n);
                ultimoOrdenadoPorNome = 1;
            } break;

            case 4: { // Insertion por tipo
                if (!temDados) { printf("\n⚠️ Cadastre primeiro.\n"); break; }
                memcpy(trabalho, base, sizeof(Componente) * n);
                double tempo = medirTempoSort(insertionSortTipo, trabalho, n, &comp, &trocas);
                mostrarComponentes(trabalho, n);
                printf("\n📥 Insertion (por tipo) → Comparações: %ld | Movimentos: %ld | Tempo: %.6fs\n",
                       comp, trocas, tempo);
                memcpy(base, trabalho, sizeof(Componente) * n);
                ultimoOrdenadoPorNome = 0; // perdeu a ordenação por nome
            } break;

            case 5: { // Selection por prioridade
                if (!temDados) { printf("\n⚠️ Cadastre primeiro.\n"); break; }
                memcpy(trabalho, base, sizeof(Componente) * n);
                double tempo = medirTempoSort(selectionSortPrioridade, trabalho, n, &comp, &trocas);
                mostrarComponentes(trabalho, n);
                printf("\n🎯 Selection (por prioridade) → Comparações: %ld | Trocas: %ld | Tempo: %.6fs\n",
                       comp, trocas, tempo);
                memcpy(base, trabalho, sizeof(Componente) * n);
                ultimoOrdenadoPorNome = 0; // perdeu a ordenação por nome
            } break;

            case 6: { // Binária por nome
                if (!temDados) { printf("\n⚠️ Cadastre primeiro.\n"); break; }
                if (!ultimoOrdenadoPorNome) {
                    printf("\nℹ️ É necessário ordenar por NOME (opção 3) antes da busca binária.\n");
                    break;
                }
                char chave[30];
                printf("Nome do componente-chave: ");
                lerLinha(chave, sizeof(chave));

                long compBusca = 0;
                int pos = buscaBinariaPorNome(base, n, chave, &compBusca);
                if (pos >= 0) {
                    printf("\n🔑 Componente encontrado!\n");
                    printf("→ Nome: %s | Tipo: %s | Prioridade: %d\n",
                           base[pos].nome, base[pos].tipo, base[pos].prioridade);
                    printf("Comparações (binária): %ld\n", compBusca);
                    printf("\n✅ Torre pode ser ativada. Componentes (ordenados por nome):\n");
                    mostrarComponentes(base, n);
                } else {
                    printf("\n❌ Componente não encontrado.\n");
                    printf("Comparações (binária): %ld\n", compBusca);
                }
            } break;

            default:
                printf("\nOpção inválida.\n");
        }
    }

    return 0;
}
