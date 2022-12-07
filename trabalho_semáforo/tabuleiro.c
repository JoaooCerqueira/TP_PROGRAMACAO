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

void inicializa_tab(int lin, int col,char **a){
   int i,j;
   for(i=0;i<lin;i++){
        for(j=0;j<col;j++){             //coloca em todas as posições do tabuleiro '_'
            a[i][j]='_';
        }
   }
}

void mostra_tab( int *lin, int *col,char **a){
     int i,j;

     printf("  Tabuleiro %dx%d\n\n", *lin,*col);
     printf("     ");
     for(j=0;j<*col;j++){
        printf("C%d    " ,j);
     }
    printf("\n");
   for(i=0;i<*lin;i++){
        printf("L%d ",i);
    for(j=0;j<*col;j++){
        printf("[ %c ] ", a[i][j]);
    }
    printf("\n");

   }
}

char** adiciona_lin(int *lin, int *col,char **tab){
    char**aux;
    int i;

    aux =(char**) realloc(tab,sizeof(char*)*(*lin+1));          //realoca espaço para uma linha
    aux[*lin] = malloc(sizeof(char)*(*col));                    //aloca espaço para as colunas dessa linha que realocou

    if(aux==NULL){
        printf("erro na realocacao");
        return tab;
    }

    for(i=0;i<*col;i++){                                        //preenche as colunas dessa linha com '_'
        aux[*lin][i]='_';
    }

    tab=aux;
    (*lin)++;                                                   //incrementa uma linha

    return tab;
}

void adiciona_col(int *lin ,int *col, char **tab){
    int i;

    for(i=0;i<(*lin);i++){
        tab[i]= realloc(tab[i],sizeof(char)*(*col+1));      //em cada linha realoca espaço para uma coluna
        tab[i][*col]='_';                                   //preenche esses espaços com '_'
    }

    if(tab==NULL){
        printf("erro na realocacao");
        return;
    }

    (*col)++;                                               //incrementa as colunas
}

void le_tab(char**tab,int col,int lin){
    FILE *f;
    int i;

    f=fopen("jogo.bin","rb");                       //abrir ficheiro binario para ler
     if(f==NULL){
        printf("Erro na leitura do ficheiro");
        return;
    }
    fseek(f,sizeof(retoma),SEEK_SET);               //percorrer sizeof(retoma) do ficheiro binario para chegar a parte que tem a informação de cada posição do tabuleiro
      for(i=0;i<lin;i++){
           fread(tab[i],sizeof(char),col,f);        //ler essa informção para cada posição do tabuleiro
    }

    fclose(f);                                      //fechar o ficheiro
}
