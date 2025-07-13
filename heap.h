#include "funções_geradoras.h"

void heap_sort(Aluno *heap, int n);

Aluno* criar_heap(int n);

Aluno* insere_heap(Aluno *heap, int n);

void constroi_heap_maximo(Aluno *heap, int n);

Aluno* exclui_heap(Aluno* heap,int n);

Aluno* aumentar(Aluno *heap, int n);