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

pjogadas insere_jogadas(pjogadas p, char**tab, int col, int lin, int contador){
    pjogadas novo,aux;
    int i;

    //alocar espaco para nova jogada
    novo=malloc(sizeof(jogadas));
    if(novo==NULL)
        return p;

    //prencher a jogada
    novo->contador=contador;

    novo->lin=lin;
    novo->col=col;

    novo->tab = malloc(sizeof(char*)*lin);
                for(int i = 0; i < lin; i++)
                    novo->tab[i] = malloc(sizeof(char)*col);

    for(i=0;i<lin; i++){
        for(int j=0;j<col;j++){
            novo->tab[i][j]=tab[i][j];
        }
    }
    novo->prox=NULL;
    ///////////////////////////////

    //colocar jogada no final
    if(p==NULL)
        p=novo;
    else{
        aux=p;
        while(aux->prox!=NULL)
            aux=aux->prox;

        aux->prox=novo;
        novo->prox=NULL;
    }

    return p;
}

void guarda_lista(pjogadas lista, int cont){
    FILE *f;
    int i,j;
    char nome_fich[15];

    printf("\n\nNome do ficheiro .txt: ");      //nome para colocar no fihceiro
    scanf("%s", nome_fich);

    f=fopen(nome_fich,"wt");                    //abrir o ficheiro de texto para escrever
    if(f==NULL){
        printf("erro no acesso ao ficheiro");
        return;
    }


    //colocar a informação da lista no ficheiro de texto
    do{
        fprintf(f,"jogada: %d\n", lista->contador);
        fprintf(f,"     ");
        for(j=0;j<lista->col;j++){
            fprintf(f,"C%d    " ,j);
        }
            fprintf(f,"\n");
        for(i=0;i<lista->lin;i++){
            fprintf(f,"L%d ",i);
            for(j=0;j<lista->col;j++){
                fprintf(f,"[ %c ] ", lista->tab[i][j]);
            }
            fprintf(f,"\n");
        }
        fprintf(f,"\n");
     lista=lista->prox;

    }while(lista->prox!=NULL);
       fprintf(f,"jogada: %d\n", lista->contador);
       fprintf(f,"     ");
        for(j=0;j<lista->col;j++){
            fprintf(f,"C%d    " ,j);
        }
            fprintf(f,"\n");
        for(i=0;i<lista->lin;i++){
            fprintf(f,"L%d ",i);
            for(j=0;j<lista->col;j++){
                fprintf(f,"[ %c ] ", lista->tab[i][j]);
            }
            fprintf(f,"\n");
        }

    if(cont%2==0){
        fprintf(f,"\nO jogador B ganhou!\n\n");
    }else{
        fprintf(f,"\nO jogador A ganhou!\n\n");
    }
    //////////////////////////////////////////////////

        fclose(f);      //fechar o ficheiro
}

void mostra_info(pjogadas p, int aux, int cont){
    int i;


    for(i=0;i<cont-aux;i++)             //percorrer a lista ligada ate chegar a posicao cont-aux
        p=p->prox;

      for(i=0;i<aux;i++){                       //esccrever as aux jogadas anteriores
        printf("\n");
        printf("jogada %d\n",p->contador);
        mostra_tab(&p->lin,&p->col,p->tab);
        printf("\n");
        p=p->prox;
}
    printf("\n\n");
}
