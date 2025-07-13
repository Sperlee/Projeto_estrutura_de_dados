#include "funções_geradoras.h"

typedef Aluno *Hash;

Aluno* inicializarTabela();

int inserir_hash(Aluno tabela[], Aluno novo);

int buscar(Aluno tabela[], const char *cpf);

int remover_hash(Aluno tabela[], const char *cpf);