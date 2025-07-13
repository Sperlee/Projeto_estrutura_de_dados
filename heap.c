#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "funções_geradoras.h"

Aluno* criar_heap(int n){
    Aluno *heap = (Aluno*)malloc(sizeof(Aluno)*(n+1));

    if(heap == NULL){
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }

    return heap;
}

int pai(int i){
    return i/2;
}

int esq(int i){
    return i*2;
}

int dir(int i){
    return (i*2)+1;
}

void subir(Aluno *heap, int i) {
    while (i > 1) {
        int j = pai(i);

        if (heap[i].nota > heap[j].nota) {
            // Troca toda a estrutura Aluno
            Aluno temp = heap[i];
            heap[i] = heap[j];
            heap[j] = temp;

            i = j; // Continua subindo
        } else {
            break; // Propriedade de heap máxima satisfeita
        }
    }
}

void descer(Aluno *heap, int i, int n) {
    int e = esq(i);
    int d = dir(i);
    int maior = i;

    if (e <= n && heap[e].nota > heap[i].nota) {
        maior = e;
    }
    if (d <= n && heap[d].nota > heap[maior].nota) {
        maior = d;
    }
    if (maior != i) {
        Aluno temp = heap[i];
        heap[i] = heap[maior];
        heap[maior] = temp;
        descer(heap, maior, n);
    }
}

Aluno* aumentar(Aluno *heap, int n) {
    Aluno *novo_heap = (Aluno *) realloc(heap, sizeof(Aluno) * (n + 2));
    if (novo_heap == NULL) {
        printf("Erro ao realocar memória.\n");
        free(heap); // Libera a memória antiga em caso de falha
        exit(1);
    }
    return novo_heap;
}


Aluno* insere_heap(Aluno *heap, int n) {
    subir(heap, n);

    return heap;
}

Aluno* exclui_heap(Aluno *heap, int n) {
    heap[1] = heap[n];
    (n)--;

    heap = (Aluno *) realloc(heap, sizeof(Aluno) * (n + 1));
    if (heap == NULL && n > 0) {
        printf("Erro ao realocar memória.\n");
        exit(1);
    }

    descer(heap, 1, n);

    return heap;
}

void constroi_heap_maximo(Aluno *heap, int n){
    int i;
    int j=(n/2);
    for(i=j;i>=1;i--){
        descer(heap, i, n);
    }
}

void heap_sort(Aluno *heap, int n) {
    constroi_heap_maximo(heap, n);
    for (int i = n; i > 1; i--) {
        Aluno temp = heap[i];
        heap[i] = heap[1];
        heap[1] = temp;

        descer(heap, 1, i - 1);
    }
}