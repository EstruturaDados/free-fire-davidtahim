#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 10 // tamanho da lista (pode alterar para testar listas maiores)

// ========== FUNÇÕES DE GERAÇÃO ==========
void gerarListaOrdenada(int v[], int n) {
    for (int i = 0; i < n; i++)
        v[i] = i + 1;
}

void gerarListaInversa(int v[], int n) {
    for (int i = 0; i < n; i++)
        v[i] = n - i;
}

void gerarListaAleatoria(int v[], int n) {
    for (int i = 0; i < n; i++)
        v[i] = rand() % 100; // números entre 0 e 99
}

void copiarVetor(int origem[], int destino[], int n) {
    for (int i = 0; i < n; i++)
        destino[i] = origem[i];
}

void imprimirVetor(int v[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}

// ========== ALGORITMOS DE ORDENAÇÃO ==========

// Bubble Sort
void bubbleSort(int v[], int n, long *comp, long *trocas) {
    *comp = *trocas = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            (*comp)++;
            if (v[j] > v[j + 1]) {
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
                (*trocas)++;
            }
        }
    }
}

// Insertion Sort
void insertionSort(int v[], int n, long *comp, long *trocas) {
    *comp = *trocas = 0;
    for (int i = 1; i < n; i++) {
        int chave = v[i];
        int j = i - 1;
        while (j >= 0 && v[j] > chave) {
            (*comp)++;
            v[j + 1] = v[j];
            j--;
            (*trocas)++;
        }
        if (j >= 0)
            (*comp)++;
        v[j + 1] = chave;
    }
}

// Selection Sort
void selectionSort(int v[], int n, long *comp, long *trocas) {
    *comp = *trocas = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            (*comp)++;
            if (v[j] < v[min])
                min = j;
        }
        if (min != i) {
            int temp = v[i];
            v[i] = v[min];
            v[min] = temp;
            (*trocas)++;
        }
    }
}

// ========== TESTE E COMPARAÇÃO ==========
int main() {
    srand(time(NULL));
    int original[TAM], v[TAM];
    long comp, trocas;
    clock_t inicio, fim;
    double tempo;

    int tipo;
    do {
        printf("\n=== COMPARADOR DE MÉTODOS DE ORDENAÇÃO ===\n");
        printf("1. Lista já ordenada (melhor caso)\n");
        printf("2. Lista inversa (pior caso)\n");
        printf("3. Lista aleatória (caso médio)\n");
        printf("0. Sair\n> ");
        scanf("%d", &tipo);

        if (tipo == 0) break;

        switch (tipo) {
            case 1: gerarListaOrdenada(original, TAM); break;
            case 2: gerarListaInversa(original, TAM); break;
            case 3: gerarListaAleatoria(original, TAM); break;
            default: printf("Opção inválida!\n"); continue;
        }

        printf("\nLista original:\n");
        imprimirVetor(original, TAM);

        // BUBBLE SORT
        copiarVetor(original, v, TAM);
        inicio = clock();
        bubbleSort(v, TAM, &comp, &trocas);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        printf("\n🫧 Bubble Sort:\n");
        imprimirVetor(v, TAM);
        printf("Comparações: %ld | Trocas: %ld | Tempo: %.5fs\n", comp, trocas, tempo);

        // INSERTION SORT
        copiarVetor(original, v, TAM);
        inicio = clock();
        insertionSort(v, TAM, &comp, &trocas);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        printf("\n📥 Insertion Sort:\n");
        imprimirVetor(v, TAM);
        printf("Comparações: %ld | Trocas: %ld | Tempo: %.5fs\n", comp, trocas, tempo);

        // SELECTION SORT
        copiarVetor(original, v, TAM);
        inicio = clock();
        selectionSort(v, TAM, &comp, &trocas);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        printf("\n🎯 Selection Sort:\n");
        imprimirVetor(v, TAM);
        printf("Comparações: %ld | Trocas: %ld | Tempo: %.5fs\n", comp, trocas, tempo);

    } while (tipo != 0);

    printf("\nEncerrando o programa...\n");
    return 0;
}
