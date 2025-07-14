#ifndef ARVOREBMAIS_H
#define ARVOREBMAIS_H

#include <stdio.h>

#define ORDEM 4 // Ordem da Árvore B+

// Estrutura de um nó da Árvore B+
typedef struct No {
    int numChaves; // Número de chaves no nó
    int chaves[ORDEM - 1]; // Chaves armazenadas no nó
    struct No* filhos[ORDEM]; // Ponteiros para os filhos
    int ehFolha; // Indica se o nó é uma folha (1 para folha, 0 para não folha)
} No;

// Estrutura da Árvore B+
typedef struct {
    No* raiz; // Ponteiro para a raiz da Árvore B+
} ArvoreBMais;

// Funções principais da Árvore B+
ArvoreBMais* inicializarArvoreBMais();
void inserirArvoreBMais(ArvoreBMais* arvore, int chave);
int buscarArvoreBMais(No* no, int chave);
void imprimirArvoreBMais(No* no);
void salvarArvoreBMais(No* no, FILE* arq);

// Funções auxiliares para manipulação de nós
No* criarNo(int ehFolha);
void inserirNo(No* no, int chave, No** novaRaiz);
void dividirNo(No* no, No** novoNo);

void criarArquivoIndices(const char* arquivoRegistros, const char* arquivoIndices);


#endif // ARVOREBMAIS_H