//-----------------------------//
// João Cerqueira - 2020141650 //
//-----------------------------//

#ifndef JOGADA_H_INCLUDED
#define JOGADA_H_INCLUDED

typedef struct joga jogadas, *pjogadas;
int adiciona_pedra(int lin, int col, char **a, jogador aux);
int adicionar_peca(int lin,int col,char **a);
char **jogada_jogo(int *lin,int *col, char** tabuleiro, int *cont, jogador *b, jogador *a,retoma *jogo,pjogadas *lista, int *termina,int ret);
char **jogada_bot(int *lin,int *col, char** tabuleiro, int *cont, jogador *b,pjogadas *lista);
int verifica_vic(int lin, int col, char **a, jogador aux);

#endif // JOGADA_H_INCLUDED
