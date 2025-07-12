#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funções_geradoras.h"
#include "heap.h"

#define TAMANHO_HEAP 10000

void main(){
    int acao = -1;
    int resposta;
    while(acao != 0){

        printf("Digite o numero da ação que deseja executar:\n");
        printf("1.Gerar documento de alunos.\n");
        printf("2.Organizar arquivos em uma heap sendo a prioridade a nota.\n");
        scanf("%d",&acao);

        switch (acao){
            case 1://---------------------------------- GEERAR ARQUIVO BINARIO-----------------------------------------------------------------
            
                gerador_arquivo_bin();
                printf("Deseja printar o arquivo? sim(1) não(0)\n");

                scanf("%d", &resposta);

                if (resposta == 1) {
                    printa_arquivo_bin();
                }
                break;


            case 2://----------------------------- HEAP ---------------------------------------------------

                int *heap = criar_heap(TAMANHO_HEAP);

                FILE* arq;
                Aluno aluno;

                arq = fopen("registros.bin","rb");
                if(arq == NULL){
                    printf("Nao foi possivel abrir o arquivo bin.\n");
                    exit(1);
                }

                for(int i = 0;i < TAMANHO_HEAP;i++){
                    if(fread(&aluno,sizeof(Aluno),1,arq)){
                        heap[i+1] = aluno.nota;
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

                printf("Deseja imprimir a lista com todas as notas em prioridade?");
                printf("Se sim(1) se nao(2):\n");
                scanf("%d",&resposta);
                if(resposta == 1){
                    for(int i = 0;i <TAMANHO_HEAP+1;i++){
                        printf("%d ",heap[i+1]);
                    }
                }
                printf("\n");
                free(heap);
                break;
                
            case 3:
        }
    printf("Deseja continuar?Sim(1) Nao(0)\n");
    scanf("%d",&acao);
    }
}