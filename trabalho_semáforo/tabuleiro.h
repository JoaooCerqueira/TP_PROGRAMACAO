//-----------------------------//
// João Cerqueira - 2020141650 //
//-----------------------------//

#ifndef TABULEIRO_H_INCLUDED
#define TABULEIRO_H_INCLUDED

void inicializa_tab(int lin, int col,char **a);
void mostra_tab( int *lin, int *col,char **a);
char** adiciona_lin(int *lin, int *col,char **tab);
void adiciona_col(int *lin ,int *col, char **tab);
void le_tab(char**tab,int col,int lin);

#endif // TABULEIRO_H_INCLUDED
