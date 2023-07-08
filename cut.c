#include <stdio.h>
#include <stdlib.h>
#include "listas.h"

/* as funçoes desse código sao de uso exclusivamente da função "-cut" */

/* verificaçao da integridade dos arquivos, retorna 0 ou 1 */
int verific(FILE *dna, FILE *enzima){
	char c = fgetc(dna);
	int ver = 0;
	
	if (dna == NULL || enzima == NULL)
		return 0;
		
	while (c != EOF){
		if ((c != 'A' && c != 'a') && (c != 'C' && c != 'c') && (c != 'G' && c != 'g') && (c != 'T' && c != 't') && (c != ' '))
			ver=ver+1;
		c = fgetc(dna);
	}
	
	if (ver > 1)
		return 0;
	ver = 0 ;
	c = fgetc(enzima);
	
	while (c != EOF){
		if ((c != 'A') && (c != 'C') && (c != 'G') && (c != 'T'))
			ver=ver+1;
		c = fgetc(enzima);
	}
	
	if (ver > 1)
		return 0;
	rewind (dna);
	rewind (enzima);
	return 1;
}



/*funçao de comparaçao, retorna 1 ou 0*/
int comparacao(int tamenz, nol* p, FILE *enzima){
	nol *l = p;
	int cont = 0;
	int ver = 0;
	rewind(enzima);
	char c = fgetc(enzima);
	
	while (1){
		if ((l->dado == c) || (l->dado-32 ==  c)){
			cont = cont+1;
			c = fgetc(enzima);
		}
		else
			return 0;
		ver = ver+1;
		
		if (cont == tamenz-1)
			return 1;
			
		if (ver == tamenz-1)
			return 0;
		l = l->prox;
	}
}

/*Busca o casamento da enzima dentro do DNA utiliziando a funçao comparaçao*/
/* retorna 1 se for verdadeiro, 0 para falso */
int encontra(cadeia* l, FILE *enzima, int tamenz, int *po){
	nol *p = l->prim;
	*po = p->pos;
	
	while ((p->pos)+tamenz-2 <= l->tam){
		
		if (comparacao(tamenz,p,enzima) == 1)
			return 1;
		else{
			if (p->prox != NULL && p->prox != l->prim){
				p = p->prox;
				*po = p->pos;
			}
			else
				break;
		}
	}
	return 0;
}

/*funçao que cria o novo segmento de uma cadeia com casamento encontrando*/
/*tambem faz a indicaçao das pontas cegas e adesivas da cadeia e o segmento*/
void separa(cadeia *l, int pos, int tamenz){
	if (l->form == circular){
		l->prim->ant = NULL;
		l->ult->prox = NULL;
	}
	
	nol* p = l->prim;
	
	while (p->pos != pos){
		p = p->prox;
	}
	
	if (p->prox != NULL){
		nol *s = p->prox;
		s->ant = NULL;
		cadeia *new = malloc(sizeof(cadeia));
		new->prim = s;
		new->ult = l->ult;
		l->ult = p;
		p->prox = NULL;
		new->form = linear;
		new->proxima = l->proxima;
		l->proxima = new;
		
		/* indica ponta cega */
		l->ult->tipob = cega;
		
		if (l->ult->dado >= 'A' && l->ult->dado <= 'Z')
			l->ult->dado = l->ult->dado+32;
			
		reindexa (new);
		reescalona (l, new);
			
		/*indica as pontas adesivas*/
		int av=tamenz-2;
		nol *u=new->prim;
		
		while (av != 0){
			u->tipob = adesiva;
			if (u->dado >= 'A' && u->dado <= 'Z')
				u->dado = u->dado+32;
			u = u->prox;
			av = av-1;
		}
		new->anterior = l;
		l->proxima = new;
	}
		
	else{
		l->ult->tipob = cega;
		if (l->ult->dado >= 'A' && l->ult->dado <= 'Z')
			l->ult->dado = l->ult->dado+32;
	}
}
		
/*funçao que resume o procedimento de corte*/
void corte(lista *g, FILE *enzima, int tamenz){
	cadeia *i = g->pri;
	int po;
	
	while (i != NULL){
		if (encontra(i,enzima,tamenz,&po) == 1)
			separa(i,po,tamenz);
		i = i->proxima;
	}
	
	i = g->pri;
	while (i->proxima != NULL){ i = i->proxima;}
	g->ulti = i;
}

/* avalia o tamanho da enzima */
int tam(FILE *enzima){
	char c = fgetc(enzima);
	int tam = 0;
	while (c != EOF){
		tam = tam+1;
		c = fgetc(enzima);
	}
	return tam;
}
