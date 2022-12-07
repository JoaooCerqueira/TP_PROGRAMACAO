//-----------------------------//
// Jo�o Cerqueira - 2020141650 //
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
    fread(a, sizeof(retoma),1,f);       //ler para a estrutura de dados retoma a informa��o que est� no ficheiro bin�rio

    fclose(f);                          //fechar o ficheiro
}

void guarda_dados(retoma *a,int lin,int col, char** tab){
    FILE *f;
    int i;

    f = fopen("jogo.bin"," wb");                    //abrir o ficheiro bin�rio para escrever
    if( f== NULL){
        printf("Erro no acesso ao ficheiro");
        return;
    }

    fwrite(a,sizeof(retoma),1,f);                   //passar o que est� na struct retoma para o ficheiro bin�rio

    for(i=0;i<lin;i++){
            fwrite(tab[i],sizeof(char),col,f);      //passar o que est� em cada posi��o do tabueliro para o ficheiro bin�rio
    }

    fclose(f);                                      //fechar o ficheiro
}
