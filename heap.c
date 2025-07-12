#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "funções_geradoras.h"

int* criar_heap(int n){
    int *heap = (int*)malloc(sizeof(int)*(n+1));

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

void subir(int *heap, int i) {
    int j = pai(i);

    if (j >= 1) {
        if (heap[i] > heap[j]) {
        int temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
        subir(heap, j);
        }
    }
}

void descer(int *heap, int i, int n){
    int e = esq(i);
    int d = dir(i);
    int maior = i;
        if (e<=n && heap[e] > heap[i]) {
            maior=e;
        }
        if (d<=n && heap[d] > heap[maior]) {
            maior=d;
        }
        if (maior != i){
            int temp=heap[i];
            heap[i] = heap[maior];
            heap[maior]=temp;
            descer(heap, maior, n);
        }
}

int insere(int *heap, int novo, int n) {
    heap = (int *) realloc(heap, sizeof(int) * (n + 2));
    n = n + 1;
    heap[n] = novo;

    subir(heap, n);

    return n;
}

int exclui(int *heap, int n) {
    heap[1] = heap[n];
    n = n - 1;

    heap = (int *) realloc(heap, sizeof(int) * (n + 1));
    descer(heap, 1, n);

    return n;
}

void constroi_heap_maximo(int *heap, int n){
    int i;
    int j=(n/2);
    for(i=j;i>=1;i--){
        descer(heap, i, n);
    }
}

void heap_sort(int *heap, int n){
    int i;
    int j=n;
    constroi_heap_maximo(heap, n);
    for(i=n;i>1;i--){
        int temp=heap[i];
        heap[i]=heap[1];
        heap[1]=temp;
        j--;
        descer(heap, 1, j);
    }
}