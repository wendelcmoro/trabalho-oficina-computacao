#ifndef _cut_
#define _cut_
#include "listas.h"

int encontra(cadeia* l, FILE *enzima,int tamenz, int *po);
int comparacao(int tamenz, nol* p, FILE *enzima);
void separa(cadeia *l, int pos, int tamenz);
void corte(lista *g,FILE *enzima, int tamenz);
int tam(FILE *enzima);
int verific(FILE *dna, FILE *enzima);

#endif
