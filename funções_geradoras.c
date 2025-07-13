#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "funções_geradoras.h"

#define MIN 97
#define MAX 122

#define MIN_CPF 48
#define MAX_CPF 57



void gerar_nome(char vetor[]){
    for(int i = 0;i < 11;i++){//onde devo alterar caso o nome esteja pequeno demais
        vetor[i] = 'a' + rand() % 26;
    }
    vetor[11] = '\0';
}

void gerar_cpf(char cpf[12]) {
    for (int i = 0; i < 11; i++) {
        cpf[i] = '0' + (rand() % 10); // Gera um dígito aleatório de '0' a '9'
    }
    cpf[11] = '\0'; // Adiciona o caractere nulo ao final
}


int gerar_nota(){
    return (rand() % 100);
}

void printa_arquivo_bin() {
    FILE* arq = fopen("registros.bin", "rb");
    if (arq == NULL) {
        printf("Erro ao abrir arquivo para leitura.\n");
        return;
    }

    Aluno aluno;
    while (fread(&aluno, sizeof(Aluno), 1, arq)) {
        printf("cpf: %-12s nome: %-11s nota: %d\n", aluno.cpf, aluno.nome, aluno.nota);
    }

    fclose(arq);
}

void gerador_arquivo_bin(){
    FILE* arq = fopen("registros.bin", "wb");

    if(arq == NULL){
        printf("Erro ao gerar arquivo bin.\n");
    }

    Aluno aluno;

    for (int i = 1; i < 10001; i++) {
        gerar_nome(aluno.nome);
        gerar_cpf(aluno.cpf);
        aluno.nota = gerar_nota();
        fwrite(&aluno, sizeof(Aluno), 1, arq);
    }

    fclose(arq);
}