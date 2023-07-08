#ifndef _listas_
#define _listas_

enum tipo{ adesiva, cega, normal};

enum forma{linear,circular};
	
typedef struct nol{
	int pos;
	char dado;
	struct nol* prox;
	struct nol* ant;
	enum tipo tipob;	
}nol;

typedef struct CadeiaDNA{
	int tam, info;
	nol* prim;
	nol* ult;	
	struct CadeiaDNA *proxima, *anterior;
	enum forma form;
}cadeia;

typedef struct Lista{
	cadeia* pri;
	cadeia* ulti;
}lista;

cadeia* cria();
lista* crea();
void liga(lista *g, cadeia *l);
void apontanovacadeia(cadeia *k, lista *g);
void insere(cadeia* l, char i, int *po);
void impr(lista *g);
void invertecadeias(cadeia *l, cadeia *b);
void imprGlue(lista *l, lista *g);
void destroicadeia(cadeia *l);
void imprGlueApenasCadeia(cadeia *l);
void reescalona(cadeia *l, cadeia *x);
void reindexa(cadeia *l);
void avalia(lista *g, cadeia *l, FILE *DNA, int ehcircular);
void imprRecombinecadeia(cadeia *l);
void imprRecombinefail(lista *g);

#endif
