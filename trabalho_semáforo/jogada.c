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

int adiciona_pedra(int lin, int col, char **a, jogador aux){

    if(aux.pedra!=0 && a[lin][col]== '_'){          //se na estrutura do jogador aux ainda tiver pedra, coloca na posicao que escolheu uma pedra
        a[lin][col]='P';
        return 1;
    }
    printf("\n");                                   //senao a jogada é invalida
    printf("jogada invalida");
    printf("\n\n");
    return 0;
}

int adicionar_peca(int lin,int col,char **a){
    int flag=0;
    switch(a[lin][col]){                            // se na posicao que o jogador escolheu estiver '_','G' ou 'Y' o jogador coloca uma peça la
        case '_':
            a[lin][col]='G';
            flag=1;
            break;
        case 'G':
            a[lin][col]='Y';
            flag=1;
            break;
        case 'Y':
            a[lin][col]='R';
            flag=1;
            break;
        case 'R':                                   //se na posicao que o jogador escolheu estiver 'P' ou 'R' a jogada é inválida
            printf("\njogada invalida\n\n");
            flag=0;
            break;
        case 'P':
            printf("\njogada invalida\n\n");
    }
    return flag;
}

char **jogada_jogo(int *lin,int *col, char** tabuleiro, int *cont, jogador *b, jogador *a,retoma *jogo,pjogadas *lista, int *termina, int ret){
    int jogada;
    int lin_aux;
    int col_aux;
    int aux_pedra;
    int k;
    int flag;
    int i;

            printf("\n");
            printf("--------------------------------------\n");
            if((*cont)%2==0)
                mostra_jogador(*a);
            else
                mostra_jogador(*b);
            if(ret==1){
            printf("--------------------------------------\n");
            printf("     Opcoes de jogada:\n");
            printf("\t1.colocar uma peca\n\t2.colocar uma pedra\n\t3.adicionar linha\n\t4.adicionar coluna"
                    "\n\t5.ver jogadas anteriores\n\t6.terminar jogo\n");
            }else{
                printf("--------------------------------------\n");
                printf("     Opcoes de jogada:\n");
                printf("\t1.colocar uma peca\n\t2.colocar uma pedra\n\t3.adicionar linha\n\t4.adicionar coluna\n");
            }

        do{
            printf("\n   Escolha a sua jogada: ");
            scanf("%d", &jogada);
            flush_in();
            printf("\n");

            switch(jogada){
                case 1:
                    do{
                        printf("   Numero da linha: ");
                        scanf("%d", &lin_aux);
                        flush_in();
                    }while(lin_aux<0 || lin_aux>=*lin);

                    do{
                        printf("   Numero da coluna: ");
                        scanf("%d", &col_aux);
                        flush_in();
                        printf("\n\n");
                    }while(col_aux<0 || col_aux>=*col);

                    flag=adicionar_peca(lin_aux,col_aux,tabuleiro);
                    *lista=insere_jogadas(*lista,tabuleiro,*col,*lin,*cont);

                    mostra_tab(&(*lin),&(*col),tabuleiro);
                    if(flag==1)
                        (*cont)++;
                    break;

                case 2:
                    if((*cont)%2==0){
                    if(a->pedra==0){
                        printf("\nja nao tem pedras para adicionar\n");
                        break;
                    }
                    }else{
                         if(b->pedra==0){
                        printf("\nja nao tem pedras para adicionar\n");
                        break;
                        }
                    }
                    do{
                        do{
                            printf("linha onde quer adicionar: ");
                            scanf("%d", &lin_aux);
                            flush_in();
                        }while(lin_aux<0 || lin_aux>=*lin);

                        do{
                            printf("coluna onde quer adicionar: ");
                            scanf("%d", &col_aux);
                            flush_in();
                        }while(col_aux<0 || col_aux>=*col);

                        if((*cont)%2==0)
                            aux_pedra=adiciona_pedra(lin_aux,col_aux,tabuleiro,*a);
                        else
                            aux_pedra=adiciona_pedra(lin_aux,col_aux,tabuleiro,*b);
                    }while(aux_pedra==0);

                    *lista=insere_jogadas(*lista,tabuleiro,*col,*lin,*cont);
                    mostra_tab(&(*lin),&(*col),tabuleiro);

                    if((*cont)%2==0)
                            a->pedra--;
                        else
                            b->pedra--;
                    (*cont)++;
                    break;

                case 3:
                    if((*cont)%2==0){
                        if(a->Col_linExtra!=0){
                            tabuleiro=adiciona_lin(&(*lin),&(*col),tabuleiro);

                            a->Col_linExtra--;


                        *lista=insere_jogadas(*lista,tabuleiro,*col,*lin,*cont);
                        mostra_tab(&(*lin),&(*col),tabuleiro);

                        (*cont)++;

                        }else
                            printf("\tNao pode adicionar mais linhas");
                            break;

                    }else{
                         if(b->Col_linExtra!=0){
                            tabuleiro=adiciona_lin(&(*lin),&(*col),tabuleiro);

                            b->Col_linExtra--;

                            *lista=insere_jogadas(*lista,tabuleiro,*col,*lin,*cont);
                            mostra_tab(&(*lin),&(*col),tabuleiro);

                            (*cont)++;
                            }else
                                printf("\tNao pode adicionar mais linhas");
                                break;
                    }

                case 4:
                    if((*cont)%2==0){
                        if(a->Col_linExtra!=0){
                            adiciona_col(&(*lin),&(*col),tabuleiro);

                            a->Col_linExtra--;
                            mostra_jogador(*a);

                            *lista=insere_jogadas(*lista,tabuleiro,*col,*lin,*cont);
                            mostra_tab(&(*lin),&(*col),tabuleiro);
                            (*cont)++;
                        }else
                            printf("\tNao pode adicionar mais colunas");
                            break;

                    }else{
                        if(b->Col_linExtra!=0){
                            adiciona_col(&(*lin),&(*col),tabuleiro);

                            b->Col_linExtra--;
                            mostra_jogador(*b);

                            *lista=insere_jogadas(*lista,tabuleiro,*col,*lin,*cont);
                            mostra_tab(&(*lin),&(*col),tabuleiro);
                            (*cont)++;
                            }else
                                printf("\tNao pode adicionar mais colunas");
                                break;
                        }

                case 5:
                    do{
                    printf("numero de jogadas que quer ver: ");
                    scanf("%d", &k);
                    flush_in();
                    }while(k>*cont || k<=0);
                    mostra_info(*lista,k,*cont);
                    break;

                case 6:
                    jogo->a=*a;
                    jogo->b=*b;
                    jogo->col=*col;
                    jogo->lin=*lin;
                    jogo->contador=*cont;
                    jogo->tabuleiro = malloc(sizeof(char*)*(*lin));
                    for(int i = 0; i < *lin; i++)
                        jogo->tabuleiro[i] = malloc(sizeof(char)*(*col));

                    for(i=0;i<*lin; i++){
                        for(int j=0;j<*col;j++){
                            jogo->tabuleiro[i][j]=tabuleiro[i][j];
                        }
                    }
                    guarda_dados(&(*jogo),*lin,*col,tabuleiro);
                    (*termina)=1;
            }
        }while(jogada<1 || jogada>6);

return tabuleiro;
}

char **jogada_bot(int *lin,int *col, char** tabuleiro, int *cont, jogador *b,pjogadas *lista){
    int bot_lin;
    int bot_col;
    int aux_pedra;
    int flag=0;
    int bot_jogada;


    printf("\n");
    printf("--------------------------------------\n");
    mostra_jogador(*b);
    printf("--------------------------------------\n");

    do{
        bot_jogada= intUniformRnd(1,4);
        printf("\n");


        switch(bot_jogada){
            case 1:
                bot_lin= intUniformRnd(0,(*lin)-1);
                bot_col= intUniformRnd(0,(*col)-1);
                printf("\n\n");

                flag=adicionar_peca(bot_lin,bot_col,tabuleiro);
                mostra_tab(&(*lin),&(*col),tabuleiro);

                if(flag==1){
                    *lista=insere_jogadas(*lista,tabuleiro,*col,*lin,*cont);
                    (*cont)++;
                }
                break;

            case 2:
                if(b->pedra==0){
                    printf("\nja nao tem pedras para adicionar\n");
                    break;
                }

                do{
                    bot_lin=intUniformRnd(0,(*lin)-1);
                    bot_col=intUniformRnd(0,(*col)-1);
                    aux_pedra=adiciona_pedra(bot_lin,bot_col,tabuleiro,*b);
                }while(aux_pedra==0);

                mostra_tab(&(*lin),&(*col),tabuleiro);
                *lista=insere_jogadas(*lista,tabuleiro,*col,*lin,*cont);
                (*cont)++;
                b->pedra--;
                break;

            case 3:
                if(b->Col_linExtra!=0){
                    tabuleiro=adiciona_lin(&(*lin),&(*col),tabuleiro);
                    b->Col_linExtra--;
                    mostra_tab(&(*lin),&(*col),tabuleiro);
                    *lista=insere_jogadas(*lista,tabuleiro,*col,*lin,*cont);
                    (*cont)++;
                    break;
                }else
                    printf("\n\tNao pode adicionar mais linhas\n");
                    break;

            case 4:
                if(b->Col_linExtra!=0){
                    adiciona_col(&(*lin),&(*col),tabuleiro);
                    b->Col_linExtra--;
                    mostra_jogador(*b);
                    mostra_tab(&(*lin),&(*col),tabuleiro);
                    *lista=insere_jogadas(*lista,tabuleiro,*col,*lin,*cont);
                    (*cont)++;
                    break;

                }else
                    printf("\n\tNao pode adicionar mais colunas\n");
                break;

            case 5:

            case 6:
                return 0;
        }
    }while(bot_jogada<1 || bot_jogada>4);

    return tabuleiro;
}

int verifica_vic(int lin, int col, char **a, jogador aux){
    int i,j;
    char posicao=a[0][col-1];

  for(i=0;i<lin;i++){
        if(a[i][0] !='_'){
            for(j=0;j<col-1 && a[i][j] == a[i][j+1];j++)
                ;
            if(j==col-1){
                printf("O %s ganhou!",aux.nome);
                return 1;
            }
        }
  }

  for(j=0;j<col;j++){
        if(a[0][j] !='_'){
            for(i=0; i<lin-1 && a[i][j] == a[i+1][j];i++)
                ;
            if(i==lin-1){
                printf("O %s ganhou!",aux.nome);
                return 1;
            }
        }
    }
  if(lin==col){
    for(i=0;i<lin;i++){
        if(a[i][i] !='_'){
            for(j=0;j<lin-1 && a[j][j]==a[j+1][j+1];j++)
                ;
            if(j==lin-1){
                printf("O %s ganhou!",aux.nome);
                return 1;
            }
        }
    }

    for(i=0 ; i<lin ; i++) {
        for(j=col-1 ; j>=0 ; j--) {
            if(posicao==a[i][j] && posicao!= '_') {
                if(i==lin-1 && j==0) {
                    printf("O %s ganhou!",aux.nome);
                    return 1;
                }
            }
        }
    }

  }
    return 0;
}
