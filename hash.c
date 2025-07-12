#include "funções_geradoras.h"
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

#define NUM_DIGITOS_CPF 12

void inicializar(Hash *tab,int n){
    for(int i = 0;i < n;i++){
        tab[i] = NULL;
    }
}


Aluno *aloca(char cpf[NUM_DIGITOS_CPF],char nome[50],int nota,Hash *tab){
    Aluno *novo = (Aluno*)malloc(sizeof(Aluno));
    
    for(int i = 0;i < NUM_DIGITOS_CPF;i++){
        novo->cpf[i] = cpf[i];
    }
    
    for(int i = 0;i < 49;i++){
        novo->nome[i] = nome[i];
    }
    novo->nome[49] = '\0';

    novo->nota = nota;

    return novo;
}


int hash_linha(char cpf[NUM_DIGITOS_CPF],int n){
    int soma = 0;
    for(int i = 0;i < NUM_DIGITOS_CPF;i++){
        soma += cpf[i];
    }
    srand(soma);

    return rand() % n;
}


int hash(char cpf[NUM_DIGITOS_CPF],int n){
    return (hash_linha(cpf,n)) % n;//usei tentativa linear
}


int buscar(Hash *tab,char cpf[NUM_DIGITOS_CPF],int n){

    int pos = hash(cpf,n);
    
}