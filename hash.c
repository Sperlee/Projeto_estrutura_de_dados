#include "funções_geradoras.h"
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>

#define NUM_DIGITOS_CPF 12
#define HASH_TAM 100000
#define MARCA_REMOVIDO "REMOVIDO"



int gerarSeed(const char *cpf) {
    int seed = 0;
    for (int i = 0; i < 9 && cpf[i] != '\0'; i++) {
        if (cpf[i] >= '0' && cpf[i] <= '9') {
            seed = seed * 10 + (cpf[i] - '0');
        }
    }
    return seed;
}


int gerarHash(const char *cpf) {
    int chave = gerarSeed(cpf);
    srand(chave);
    return rand() % HASH_TAM;
}


Aluno* inicializarTabela() {
    Aluno* tabela = (Aluno*)malloc(sizeof(Aluno)*(HASH_TAM));

    if(tabela == NULL){
        printf("Problema ao alocar memoria para a tabela HASH.\n");
        exit(1);
    }

    for (int i = 0; i < HASH_TAM; i++) {
        tabela[i].cpf[0] = '\0';
    }

    return tabela;
}


int inserir_hash(Aluno* tabela, Aluno novo) {
    int h = gerarHash(novo.cpf);
    int primeiroRemovido = -1; 

    for (int i = 0; i < HASH_TAM; i++) {
        int pos = (h + i) % HASH_TAM;

        if (tabela[pos].cpf[0] == '\0') {
            
            if (primeiroRemovido != -1) pos = primeiroRemovido;

            tabela[pos] = novo;
            return pos;
        }

        if (strcmp(tabela[pos].cpf, MARCA_REMOVIDO) == 0 && primeiroRemovido == -1) {
            
            primeiroRemovido = pos;
        }

        
    }

    return -1; 
}


int buscar(Aluno tabela[], const char *cpf) {
    int h = gerarHash(cpf);

    for (int i = 0; i < HASH_TAM; i++) {
        int pos = (h + i) % HASH_TAM;

        if (tabela[pos].cpf[0] == '\0') {
            return -1; // CPF não está na tabela
        }

        if (strcmp(tabela[pos].cpf, cpf) == 0) {
            return pos; // CPF encontrado
        }
    }

    return -1; // CPF não encontrado
}


int remover_hash(Aluno tabela[], const char *cpf) {
    int pos = buscar(tabela, cpf);

    if (pos != -1) {
        strcpy(tabela[pos].cpf, MARCA_REMOVIDO);
        tabela[pos].nome[0] = '\0';
        tabela[pos].nota = -1;
        return 1;
    }

    return 0;
}