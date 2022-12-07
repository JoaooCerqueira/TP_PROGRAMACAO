//-----------------------------//
// João Cerqueira - 2020141650 //
//-----------------------------//

#ifndef RETOMA_H_INCLUDED
#define RETOMA_H_INCLUDED
typedef struct ret retoma;

typedef struct jog jogador;

struct jog{
    char nome[15];
    int Col_linExtra;
    int pedra;
};

struct ret{
    jogador a;
    jogador b;
    int contador;
    int lin;
    int col;
    char **tabuleiro;
};

void le_dados(retoma *a, char**tab);
void guarda_dados(retoma *a,int lin,int col, char** tab);

#endif // RETOMA_H_INCLUDED
