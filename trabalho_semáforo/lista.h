//-----------------------------//
// João Cerqueira - 2020141650 //
//-----------------------------//

#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

typedef struct joga jogadas, *pjogadas;

struct joga{
   int contador;
   int lin;
   int col;
   char**tab;
   pjogadas prox;
};

pjogadas insere_jogadas(pjogadas p, char**tab, int col, int lin, int contador);
void guarda_lista(pjogadas lista, int cont);
void mostra_info(pjogadas p, int aux, int cont);

#endif // LISTA_H_INCLUDED
