#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funções_geradoras.h"
#include "heap.h"
#include "hash.h"

#define TAMANHO_HEAP 10000

void main(){
    int acao = -1;
    int resposta;
    while(acao != 0){

        printf("Digite o numero da ação que deseja executar:\n");
        printf("1.Gerar documento de alunos.\n");
        printf("2.Acessar parte da HEAP.\n");
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

                            for (int i = 1; i <= novo_tamanho_heap; i++) {
                                printf("cpf: %-12s nome: %-11s nota: %d\n", heap[i].cpf, heap[i].nome, heap[i].nota);
                            }
                            printf("\n");
                            break;

                        case 3:

                            heap = exclui_heap(heap,novo_tamanho_heap);
                            printf("Elemento removido.\n");
                            break;
                                
                    }
                    printf("1.Inserir elemento\n");
                    printf("2.Imprimir a lista do arquivo HEAP.\n");
                    printf("3.Remover elemento\n");
                    printf("0.Sair da area de HEAP.\n");
                    scanf("%d",&resposta_heap);
//---------------------------------------------------------------------FIM DO MENU -----------------------------------------------------------------------------------------------
                }
            case 3://-----------------------------------------------------HASH-------------------------------------------------------------------------------


            }

        printf("Deseja continuar?Sim(1) Nao(0)\n");
        scanf("%d",&acao);

    }
}