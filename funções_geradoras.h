// funções_geradoras.h
#ifndef FUNCOES_GERADORAS_H
#define FUNCOES_GERADORAS_H

typedef struct AlunoData {
    char nome[50];
    char cpf[12];
    int nota;
} Aluno;

#endif // FUNCOES_GERADORAS_H


//gera nomes de 50 caracteres aleatorios
void gerar_nome(char vetor[]);

//gerar cps aleatorio
void gerar_cpf(char cpf[12]);

//gera notas aleatorias
int gerar_nota();

void printa_arquivo_bin();

void gerador_arquivo_bin();