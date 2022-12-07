//-----------------------------//
// João Cerqueira - 2020141650 //
//-----------------------------//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "retoma.h"
#include "tabuleiro.h"
#include "jogada.h"
#include "lista.h"

void le_dados(retoma *a, char**tab){
    FILE *f;
    f=fopen("jogo.bin","rb");           //abrir ficheiro binario para ler
    if(f==NULL){
        printf("Erro na leitura do ficheiro");
        return;
    }
    fread(a, sizeof(retoma),1,f);       //ler para a estrutura de dados retoma a informação que está no ficheiro binário

    fclose(f);                          //fechar o ficheiro
}

void guarda_dados(retoma *a,int lin,int col, char** tab){
    FILE *f;
    int i;

    f = fopen("jogo.bin"," wb");                    //abrir o ficheiro binário para escrever
    if( f== NULL){
        printf("Erro no acesso ao ficheiro");
        return;
    }

    fwrite(a,sizeof(retoma),1,f);                   //passar o que está na struct retoma para o ficheiro binário

    for(i=0;i<lin;i++){
            fwrite(tab[i],sizeof(char),col,f);      //passar o que está em cada posição do tabueliro para o ficheiro binário
    }

    fclose(f);                                      //fechar o ficheiro
}
