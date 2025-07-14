#include "funções_geradoras.h"
#include "arvoreB+.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ORDEM 4 // Ordem da Árvore B+

// Inicializa a Árvore B+
ArvoreBMais* inicializarArvoreBMais() {
    ArvoreBMais* arvore = (ArvoreBMais*) malloc(sizeof(ArvoreBMais));
    if (arvore == NULL) {
        printf("Erro ao alocar memória para a Árvore B+.\n");
        exit(1);
    }
    arvore->raiz = NULL;
    return arvore;
}

// Cria um novo nó
No* criarNo(int ehFolha) {
    No* no = (No*) malloc(sizeof(No));
    if (no == NULL) {
        printf("Erro ao alocar memória para o nó.\n");
        exit(1);
    }
    no->numChaves = 0;
    no->ehFolha = ehFolha;
    for (int i = 0; i < ORDEM; i++) {
        no->filhos[i] = NULL;
    }
    return no;
}

// Insere uma chave na Árvore B+
void inserirArvoreBMais(ArvoreBMais* arvore, int chave) {
    if (arvore->raiz == NULL) {
        // Cria um novo nó raiz
        arvore->raiz = criarNo(1);
        arvore->raiz->chaves[0] = chave;
        arvore->raiz->numChaves = 1;
    } else {
        No* novaRaiz = NULL;
        inserirNo(arvore->raiz, chave, &novaRaiz);

        if (novaRaiz != NULL) {
            // Cria uma nova raiz se a raiz atual foi dividida
            No* antigaRaiz = arvore->raiz;
            arvore->raiz = criarNo(0);
            arvore->raiz->chaves[0] = novaRaiz->chaves[0];
            arvore->raiz->filhos[0] = antigaRaiz;
            arvore->raiz->filhos[1] = novaRaiz;
            arvore->raiz->numChaves = 1;
        }
    }
}

// Insere uma chave em um nó (recursivamente)
void inserirNo(No* no, int chave, No** novaRaiz) {
    int i = no->numChaves - 1;

    if (no->ehFolha) {
        // Insere a chave no nó folha
        while (i >= 0 && chave < no->chaves[i]) {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }
        no->chaves[i + 1] = chave;
        no->numChaves++;

        // Divide o nó se necessário
        if (no->numChaves == ORDEM) {
            dividirNo(no, novaRaiz);
        }
    } else {
        // Encontra o filho onde a chave deve ser inserida
        while (i >= 0 && chave < no->chaves[i]) {
            i--;
        }
        i++;

        No* novoFilho = NULL;
        inserirNo(no->filhos[i], chave, &novoFilho);

        if (novoFilho != NULL) {
            // Insere a nova chave no nó interno
            for (int j = no->numChaves; j > i; j--) {
                no->chaves[j] = no->chaves[j - 1];
                no->filhos[j + 1] = no->filhos[j];
            }
            no->chaves[i] = novoFilho->chaves[0];
            no->filhos[i + 1] = novoFilho;
            no->numChaves++;

            // Divide o nó se necessário
            if (no->numChaves == ORDEM) {
                dividirNo(no, novaRaiz);
            }
        }
    }
}

// Divide um nó
void dividirNo(No* no, No** novoNo) {
    int meio = ORDEM / 2;
    *novoNo = criarNo(no->ehFolha);

    // Move metade das chaves para o novo nó
    for (int i = meio; i < ORDEM - 1; i++) {
        (*novoNo)->chaves[i - meio] = no->chaves[i];
        (*novoNo)->filhos[i - meio] = no->filhos[i];
        no->chaves[i] = 0;
        no->filhos[i] = NULL;
    }
    (*novoNo)->filhos[ORDEM - 1 - meio] = no->filhos[ORDEM - 1];
    no->filhos[ORDEM - 1] = NULL;

    (*novoNo)->numChaves = ORDEM - 1 - meio;
    no->numChaves = meio;
}

// Busca uma chave na Árvore B+
int buscarArvoreBMais(No* no, int chave) {
    if (no == NULL) {
        return 0; // Chave não encontrada
    }

    int i = 0;
    while (i < no->numChaves && chave > no->chaves[i]) {
        i++;
    }

    if (i < no->numChaves && chave == no->chaves[i]) {
        return 1; // Chave encontrada
    }

    if (no->ehFolha) {
        return 0; // Chave não encontrada
    }

    return buscarArvoreBMais(no->filhos[i], chave);
}

// Imprime a Árvore B+ em ordem
void imprimirArvoreBMais(No* no) {
    if (no == NULL) {
        return;
    }

    for (int i = 0; i < no->numChaves; i++) {
        if (!no->ehFolha) {
            imprimirArvoreBMais(no->filhos[i]);
        }
        printf("%d ", no->chaves[i]);
    }

    if (!no->ehFolha) {
        imprimirArvoreBMais(no->filhos[no->numChaves]);
    }
}

// Salva a Árvore B+ em um arquivo binário
void salvarArvoreBMais(No* no, FILE* arq) {
    if (no == NULL) {
        return;
    }

    for (int i = 0; i < no->numChaves; i++) {
        if (!no->ehFolha) {
            salvarArvoreBMais(no->filhos[i], arq);
        }
        fwrite(&no->chaves[i], sizeof(int), 1, arq);
    }

    if (!no->ehFolha) {
        salvarArvoreBMais(no->filhos[no->numChaves], arq);
    }
}

void criarArquivoIndices(const char* arquivoRegistros, const char* arquivoIndices) {
    FILE* arq_registros = fopen(arquivoRegistros, "rb");
    if (arq_registros == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", arquivoRegistros);
        exit(1);
    }

    FILE* arq_indices = fopen(arquivoIndices, "wb");
    if (arq_indices == NULL) {
        printf("Erro ao criar o arquivo %s.\n", arquivoIndices);
        fclose(arq_registros);
        exit(1);
    }

    Aluno temp;
    int offset = 0;

    while (fread(&temp, sizeof(Aluno), 1, arq_registros)) {
        // Extrai os 9 primeiros dígitos do CPF como chave
        char chave_cpf[10];
        strncpy(chave_cpf, temp.cpf, 9);
        chave_cpf[9] = '\0'; // Adiciona o terminador nulo

        int chave = atoi(chave_cpf); // Converte para inteiro

        // Grava a chave e o offset no arquivo de índices
        fwrite(&chave, sizeof(int), 1, arq_indices);
        fwrite(&offset, sizeof(int), 1, arq_indices);

        // Atualiza o offset para o próximo registro
        offset++;
    }

    fclose(arq_registros);
    fclose(arq_indices);

    printf("Arquivo de índices criado com sucesso: %s\n", arquivoIndices);
}

