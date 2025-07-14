#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funções_geradoras.h"
#include "heap.h"
#include "hash.h"
#include "arvoreB+.h"
#include <string.h>

#define TAMANHO_HEAP 10000
#define HASH_TAM 100000
#define MARCA_REMOVIDO "REMOVIDO"

void main(){
    int acao = -1;
    int resposta;
    while(acao != 0){

        printf("----Digite o numero da ação que deseja executar:--------\n");
        printf("--------------1.Gerar documento de alunos.--------------\n");
        printf("--------------2.Acessar parte da HEAP-------------------\n");
        printf("--------------3.Acessar parte de HASH-------------------\n");
        printf("--------------4.Acessar parte da Árvore B+--------------\n");
        scanf("%d",&acao);

        switch (acao){
            case 1://---------------------------------- GERAR ARQUIVO BINARIO-----------------------------------------------------------------

                gerador_arquivo_bin();
                printf("Deseja printar o arquivo? sim(1) não(0)\n");

                scanf("%d", &resposta);

                if (resposta == 1) {
                    printa_arquivo_bin();
                }
                break;


            case 2://------------------------------------------------------------ HEAP -----------------------------------------------------
                Aluno *heap = criar_heap(TAMANHO_HEAP);

                FILE* arq;
                Aluno aluno;

                arq = fopen("registros.bin","rb");

                if(arq == NULL){
                    printf("Nao foi possivel abrir o arquivo bin.\n");
                    exit(1);
                }
                
                for(int i = 0;i < TAMANHO_HEAP;i++){
                    if(fread(&aluno,sizeof(Aluno),1,arq)){
                        heap[i+1] = aluno;
                    }
                    else{
                        printf("Erro ao ler o arquivo ou arquivo incompleto.\n");
                        fclose(arq);
                        free(heap);
                        exit(1);
                    }
                }
                fclose(arq);
                
                constroi_heap_maximo(heap,TAMANHO_HEAP);

                FILE* arq_heap;
                arq_heap = fopen("ArquivoHeap.bin","wb");
                int novo_tamanho_heap = TAMANHO_HEAP;
                
                for(int i = 0;i < novo_tamanho_heap;i++){
                    fwrite(&heap[i+1],sizeof(Aluno),1,arq_heap);
                }

                fclose(arq_heap);

//--------------------------------------------------------------------------MENU PARA A HEAP------------------------------------------------------------------------
                int resposta_heap = -1;

                while(resposta_heap != 0){
                    switch (resposta_heap){

                        case 1:
                            while (resposta_heap == 1) {

                                novo_tamanho_heap++;

                                heap = aumentar(heap,novo_tamanho_heap);

                                printf("Digite a nota:\n");
                                scanf("%d", &heap[novo_tamanho_heap].nota);
                                printf("Digite o nome:\n");
                                scanf("%s", heap[novo_tamanho_heap].nome);
                                printf("Digite o CPF:\n");
                                scanf("%s", heap[novo_tamanho_heap].cpf);

                                heap = insere_heap(heap,novo_tamanho_heap);
                                constroi_heap_maximo(heap,novo_tamanho_heap);
                                //heap_sort(heap,novo_tamanho_heap); posso usar para ordenar a lista da HEAP


                                arq_heap = fopen("ArquivoHeap.bin","wb");
                                
                                for(int i = 0;i < novo_tamanho_heap;i++){
                                    fwrite(&heap[i+1],sizeof(Aluno),1,arq_heap);
                                }

                                fclose(arq_heap);

                                

                                printf("Deseja inserir outro elemento? Sim(1) Nao(0)\n");
                                scanf("%d", &resposta_heap);
                            }

                            break;

                        case 2:
                           
                            for (int i = 0; i < novo_tamanho_heap; i++) {
                                printf("cpf: %-12s nome: %-11s nota: %d\n", heap[i].cpf, heap[i].nome, heap[i].nota);
                            }
                            printf("\n");
                            break;

                        case 3:

                            heap = exclui_heap(heap,novo_tamanho_heap);
                            printf("Elemento removido.\n");
                            break;
                                
                    }
                    printf("-----------------1.Inserir elemento------------------\n");
                    printf("--------------2.Imprimir a lista do arquivo HEAP-----\n");
                    printf("-----------------3.Remover elemento------------------\n");
                    printf("--------------0.Sair da area de HEAP-----------------\n");
                    scanf("%d",&resposta_heap);
                }
                break;
//----------------------------------------------------------------------------...-----------------------------------------------------------------------
//----------------------------------------------------------------------------HASH-------------------------------------------------------------------------------
               
            case 3:
                //----------------criei a hash com os 10000 elementos do registro------------------------
                int resposta_hash = -1;
                FILE* arq_hash;

                // Inicializa a tabela hash
                Aluno* tabela_hash = inicializarTabela();

                // Abre o arquivo registros.bin
                arq_hash = fopen("registros.bin", "rb");
                if (arq_hash == NULL) {
                    printf("Erro ao abrir o arquivo registros.bin.\n");
                    exit(1);
                }

                // Lê os registros do arquivo e insere na tabela hash
                for (int i = 0; i < TAMANHO_HEAP; i++) {
                    Aluno temp;
                    if (fread(&temp, sizeof(Aluno), 1, arq_hash)) {
                        inserir_hash(tabela_hash, temp);
                    } else {
                        printf("Erro ao ler o arquivo ou arquivo incompleto.\n");
                        fclose(arq_hash);
                        free(tabela_hash);
                        exit(1);
                    }
                }

                // Fecha o arquivo
                fclose(arq_hash);

                printf("Tabela hash criada com os dados do arquivo registros.bin.\n");
//---------------------------------------------------------Gerador de arquivo Hash.bin -----------------------------------------------------------------          
                arq_hash = fopen("ArquivoHash.bin","wb");

                for(int i = 0;i < HASH_TAM;i++){
                    fwrite(&tabela_hash[i],sizeof(Aluno),1,arq_hash);
                }

                fclose(arq_hash);

                int novo_tamanho_hash = HASH_TAM;

 //-------------------------------------------FUNÇÕES PARA USAR A TABELA HASH--------------------------------------------------------------------------
                while(resposta_hash != 0){
                    switch (resposta_hash){
//-------------------------------------------------------------inserir elemento HASH ------------------------------------------------------------------
                        case 1:
                            while(resposta_hash == 1){
                                novo_tamanho_hash ++;
                                Aluno novo;
                                printf("Digite o CPF:\n");
                                scanf("%s",novo.cpf);
                                printf("Digite o nome:\n");
                                scanf("%s",novo.nome);
                                printf("Digite a nota:\n");
                                scanf("%d",&novo.nota);
                                int pos = inserir_hash(tabela_hash,novo);
                                
                                if(pos != -1){
                                    tabela_hash[pos] = novo;
                                    arq_hash = fopen("ArquivoHash.bin","wb");
                                    for(int i = 0;i < novo_tamanho_hash;i++){
                                        fwrite(&tabela_hash[i],sizeof(Aluno),1,arq_hash);
                                    }
                                    fclose(arq_hash);
                                }
                                else{
                                    printf("Sem espaço para mais armazenamento na tabela.\n");
                                    resposta_hash = 0;
                                }
                                printf("Deseja inserir mais um elemento?Sim(1) Nao(0)\n");
                                scanf("%d",&resposta_hash);
                                
                            }
                            break;
//---------------------------------------------------mostrar elementos da HASH-------------------------------------------------------------------
                        case 2:
                            printf("Lista de elementos na tabela HASH:\n");
                            int c = 0; // Contador de elementos válidos na tabela hash
                            for (int i = 0; i < HASH_TAM; i++) {
                                // Verifica se a posição está ocupada e não foi marcada como removida
                                if (tabela_hash[i].cpf[0] != '\0' && strcmp(tabela_hash[i].cpf, MARCA_REMOVIDO) != 0) {
                                    printf("Posição: %d | CPF: %-12s | Nome: %-11s | Nota: %d\n",
                                           i, tabela_hash[i].cpf, tabela_hash[i].nome, tabela_hash[i].nota);
                                    c++;
                                }
                            }
                            printf("\nTotal de elementos na tabela HASH: %d\n", c);
                            break;

//--------------------------------------------------------------remoção da HASH----------------------------------------------------------------------
                        case 3:
                            char temp_cpf[12];
                            printf("Digite o cpf de quem deseja remover da lista:\n");
                            scanf("%s",temp_cpf);
                            int chave_hash = buscar(tabela_hash,temp_cpf);

                            printf("removendo o aluno:  %-11s de cpf:%-12s.\n",tabela_hash[chave_hash].nome,tabela_hash[chave_hash].cpf);

                            if(remover_hash(tabela_hash,temp_cpf)){
                                printf("Removido com sucesso!!.\n");
                            }
                            else{
                                printf("Elemento não encontrado na tabela HASH,\n");
                            }
                            break;
                    }
                    printf("-----------------1.Inserir elemento----------------\n");
                    printf("--------------2.Imprimir a lista do arquivo HASH.--\n");
                    printf("-----------------3.Remover elemento----------------\n");
                    printf("--------------0.Sair da area de HASH---------------\n");
                    scanf("%d",&resposta_hash);
                }
                break;
//--------------------------------------------------------------ARVORE B+--------------------------------------------------------------------------------                
            case 4:
//---------------------------------------criei a Árvore B+ com os 10000 elementos do registro--------------------------------------
                int resposta_arvore = -1;

                ArvoreBMais* arvore = inicializarArvoreBMais();


                FILE* arq_bmais = fopen("registros.bin", "rb");
                if (arq_bmais == NULL) {
                    printf("Erro ao abrir o arquivo registros.bin.\n");
                    exit(1);
                }

                // Lê os registros do arquivo e insere na Árvore B+
                for (int i = 0; i < TAMANHO_HEAP; i++) {
                    Aluno temp;
                    if (fread(&temp, sizeof(Aluno), 1, arq_bmais)) {

                        char chave_cpf[10];
                        strncpy(chave_cpf, temp.cpf, 9);
                        chave_cpf[9] = '\0';

                        int chave = atoi(chave_cpf);
                        inserirArvoreBMais(arvore, chave); 
                    } else {
                        printf("Erro ao ler o arquivo ou arquivo incompleto.\n");
                        fclose(arq_bmais);
                        exit(1);
                    }
                }

                fclose(arq_bmais);

                printf("Árvore B+ criada com os dados do arquivo registros.bin.\n");
                criarArquivoIndices("registros.bin", "ArquivoIndices.bin");



                while (resposta_arvore != 0) {
                    printf("-----------------1.Inserir elemento----------------\n");
                    printf("--------------2.Salvar Árvore B+ em arquivo--------\n");
                    printf("--------------0.Sair da área de Árvore B+----------\n");
                    scanf("%d", &resposta_arvore);

                    switch (resposta_arvore) {
//-------------------------------------------------------------inserir elemento Árvore B+ ------------------------------------------------------------------
                        case 1: {
                            Aluno novo;
                            printf("Digite o CPF:\n");
                            scanf("%s", novo.cpf);
                            printf("Digite o nome:\n");
                            scanf("%s", novo.nome);
                            printf("Digite a nota:\n");
                            scanf("%d", &novo.nota);

                            // Extrai os 9 primeiros dígitos do CPF como chave
                            char chave_cpf[10];
                            strncpy(chave_cpf, novo.cpf, 9);
                            chave_cpf[9] = '\0'; // Adiciona o terminador nulo

                            int chave = atoi(chave_cpf); // Converte para inteiro
                            inserirArvoreBMais(arvore, chave); // Insere na Árvore B+
                            printf("Elemento inserido com sucesso na Árvore B+.\n");
                            break;
                        }
//---------------------------------------------------salvar elementos da Árvore B+ em arquivo--------------------------------------------------------
                        case 2: {
                            FILE* arq_bmais_out = fopen("ArquivoBMais.bin", "wb");
                            if (arq_bmais_out == NULL) {
                                printf("Erro ao criar o arquivo ArquivoBMais.bin.\n");
                                break;
                            }

                            salvarArvoreBMais(arvore->raiz, arq_bmais_out);
                            fclose(arq_bmais_out);
                            printf("Elementos da Árvore B+ salvos no arquivo ArquivoBMais.bin.\n");
                            break;
                        }
                        case 0:
                            printf("Saindo da área de Árvore B+.\n");
                            break;

                        default:
                            printf("Opção inválida. Tente novamente.\n");
                    }
                }
                break;
        }  

        printf("Deseja continuar?Sim(1) Nao(0)\n");
        scanf("%d",&acao);
                
    }
}
