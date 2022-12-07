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

typedef struct jog jogador;

typedef struct joga jogadas, *pjogadas;

void inicializa_jogador(jogador *a,char *nome){
    strcpy(a->nome , nome);             //coloca na struct jogador as informaçoes iniciais de cada jogador
    a->Col_linExtra=2;
    a->pedra=1;
}

void mostra_jogador(jogador a){
    printf("%s:\n",a.nome);                                                 //mostra as informações de cada jogador
    printf("Linhas ou Colunas extra disponiveis: %d\n",a.Col_linExtra);
    printf("Pedras disponiveis: %d\n", a.pedra);
}

void regras(){
    char resposta;
    scanf("%c", &resposta);
    if(resposta=='R')
        printf("\nO jogo do semaforo desenrola-se num tabuleiro dividido em celulas. No inicio, o tabuleiro"
                " esta vazio. Alternadamente os jogadores vAo colocando peças de cor Verde (G), Amarela"
                " (Y) ou Vermelha (R). Ganha o jogador que coloque uma peça que permita formar uma linha,"
                "coluna ou diagonal completa com pecas da mesma cor. As jogadas validas relativas a"
                "colocacao de pecas sao as seguintes:\n"
                "\t1. Colocar uma peca Verde numa celula vazia;\n"
                "\t2. Trocar uma peca Verde que esteja colocada no tabuleiro por uma peca Amarela;\n"
                "\t3. Trocar uma peca Amarela que esteja colocada no tabuleiro por uma peca Vermelha;\n\n"
                "Existem duas jogadas adicionais que podem ser efetuadas pelos jogadores:"
                "\t4. Colocar uma pedra numa celula vazia. Cada jogador pode colocar, no maximo, uma"
                "pedra por jogo. A colocacao de uma pedra inviabiliza que o jogo possa terminar por"
                "preenchimento da linha e coluna afetadas (e, eventualmente também da diagonal ou"
                "diagonais)."
                "\t5. Adicionar uma linha ou uma coluna ao final do tabuleiro. Esta jogada adiciona linhas"
                "ou colunas completas e vazias ao tabuleiro de jogo. Cada jogador pode efetuar esta"
                "jogada, no maximo, duas vezes por jogo.\n\n"
                "Em cada iteracao, um jogador escolhe uma destas jogadas para atualizar o tabuleiro. As"
                "jogadas 4 e 5 estao sujeitas as restricoes indicadas na sua definicao. O numero de pecas de"
                "cada cor e ilimitado.\n\n");
}

void initRandom(){
    srand(time(NULL));
}

int intUniformRnd(int a, int b){
    return a + rand()%(b-a+1);
}

void flush_in(){
    int ch;                                                         //apagar o que está no buffer
    while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}

void liberta_lista(pjogadas lista){
    pjogadas aux;                   //libertar a lista ligada
    while(lista!=NULL){
        aux = lista;
        lista = lista->prox;
        free(aux);
    }
}

int main(){
    jogador a,b;
    retoma jogo;
    pjogadas lista=NULL;
    int contador=0;
    int vitoria=0;
    initRandom();
    int lin = intUniformRnd(3,5);
    int col = lin;
    int termina=0;
    char **tabuleiro;
    int i, modo, ret;

    printf("Bem vindo ao jogo do semaforo.\nSe for a sua primeira vez a jogar prima a tecla R para verificar as"
           " regras, caso contrario prima enter.\n");
    regras();

    //aloca aspaço para o tabuleiro
    tabuleiro=(char**) malloc(sizeof(char*)*lin);
    for(i=0;i<lin;i++){
        tabuleiro[i]=malloc(sizeof(char)*col);
    }


    inicializa_jogador(&a,"jogador A");
    inicializa_jogador(&b,"jogador B");
    inicializa_tab(lin,col,tabuleiro);

    printf("\t1.Novo Jogo\n\t2.Continuar jogo\n");
    scanf("%d", &ret);
    flush_in();

    switch(ret){
        case 1:
            printf("Selecione o modo de jogo:\n");
            printf("\t1. Jogador A vs Jogador B\n\t2. Jogador A vs Computador \n");
            scanf("%d",&modo);
            flush_in();

            switch(modo){
                case 1:
                    printf("--------------------------------------\n");
                    mostra_jogador(a);
                    printf("\n");
                    mostra_jogador(b);
                    printf("--------------------------------------\n");
                    printf("\n\n");
                    mostra_tab(&lin,&col,tabuleiro);

                    while(vitoria!=1){
                        if(contador%2==0){
                            tabuleiro=jogada_jogo(&lin,&col,tabuleiro,&contador,&b,&a,&jogo,&lista,&termina,ret);
                            if(termina==1){
                                for(i=0;i<lin;i++)
                                    free(tabuleiro[i]);
                                free(tabuleiro);
                                liberta_lista(lista);
                                return 0;
                            }
                            vitoria=verifica_vic(lin,col,tabuleiro,a);

                        }else{
                            tabuleiro=jogada_jogo(&lin,&col,tabuleiro,&contador,&b,&a,&jogo,&lista,&termina,ret);
                            if(termina==1){
                                for(i=0;i<lin;i++)
                                    free(tabuleiro[i]);
                                free(tabuleiro);
                                liberta_lista(lista);
                                return 0;
                            }
                            vitoria=verifica_vic(lin,col,tabuleiro, b);
                        }
                    }
                    break;

                case 2:
                    printf("--------------------------------------\n");
                    mostra_jogador(a);
                    printf("\n");
                    mostra_jogador(b);
                    printf("--------------------------------------\n");
                    printf("\n\n");
                    mostra_tab(&lin,&col,tabuleiro);

                    while(vitoria!=1){
                        if(contador%2==0){
                            tabuleiro=jogada_jogo(&lin,&col,tabuleiro,&contador,&b,&a,&jogo,&lista,&termina,ret);
                            if(termina==1){
                                for(i=0;i<lin;i++)
                                    free(tabuleiro[i]);
                                free(tabuleiro);
                                liberta_lista(lista);
                                return 0;
                            }
                            vitoria=verifica_vic(lin,col,tabuleiro,a);

                        }else{
                            tabuleiro=jogada_bot(&lin,&col,tabuleiro,&contador,&b, &lista);
                            vitoria=verifica_vic(lin,col,tabuleiro, b);
                        }
                    }
                    break;
            }
            break;

        case 2:
            le_dados(&jogo,tabuleiro);              //le os dados da struct retoma para o jogo voltar da maneira que um jogador terminou
            //passar o que está na struct retoma para os respetivos lugares
            a=jogo.a;
            b=jogo.b;
            contador=jogo.contador;
            lin=jogo.lin;
            col=jogo.col;

            tabuleiro=(char**) malloc(sizeof(char*)*lin);
            for(i=0;i<lin;i++){
                tabuleiro[i]=malloc(sizeof(char)*col);
            }

            inicializa_tab(lin,col,tabuleiro);
            le_tab(tabuleiro,col,lin);

            printf("--------------------------------------\n");
            mostra_jogador(a);
            printf("\n");
            mostra_jogador(b);
            printf("--------------------------------------\n");
            printf("\n\n");
            mostra_tab(&lin,&col,tabuleiro);

            while(vitoria!=1){
                if(contador%2==0){
                    tabuleiro=jogada_jogo(&lin,&col,tabuleiro,&contador,&b,&a,&jogo,&lista,&termina,ret);
                    if(termina==1){
                        for(i=0;i<lin;i++)
                            free(tabuleiro[i]);
                        free(tabuleiro);
                        liberta_lista(lista);
                        return 0;
                    }
                    vitoria=verifica_vic(lin,col,tabuleiro,a);
                }else{
                   tabuleiro=jogada_jogo(&lin,&col,tabuleiro,&contador,&b,&a,&jogo,&lista,&termina,ret);
                    if(termina==1){
                        for(i=0;i<lin;i++)
                            free(tabuleiro[i]);
                        free(tabuleiro);
                        liberta_lista(lista);
                        return 0;
                    }
                    vitoria=verifica_vic(lin,col,tabuleiro, b);
                }
            }
            break;
    }
    if(ret==2){
       //libertar o tabuleiro
    for(i=0;i<lin;i++)
        free(tabuleiro[i]);
    free(tabuleiro);
    //libertar lista
    liberta_lista(lista);

    }else{
    guarda_lista(lista,contador);
    //libertar o tabuleiro
    for(i=0;i<lin;i++)
        free(tabuleiro[i]);
    free(tabuleiro);
    //libertar lista
    liberta_lista(lista);

    }
    return 0;
}
