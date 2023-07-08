#include <stdio.h>
#include <stdlib.h>
#include "listas.h"

/* funçoes encontradas aqui sao de uso exclusivo do comando "-glue" */

/* faz a comparação da ponta cega da primeira cadeia com a ponta cega da segunda cadeia */ 
int compCega(cadeia *l, cadeia *g){
	nol *p = l->ult;
	nol *b = g->ult;

	if (p->dado == b->dado)
		return 1;
		
	return 0;
}

/* faz a comparação das ponta adesivas da primeira cadeia com as pontas adesivas da segunda cadeia */
/* cria uma nova cadeia apenas com pontas adesivas para fazer a comparação, e uma vez feita essa cadeia criada é destruida */ 
int compAdesiva(cadeia *l, cadeia *g){
	if (l != NULL && g != NULL){
		
		cadeia *adesivas = cria();
		nol *p = l->prim;
		int po=0;
	
		while (p->dado >= 'a' && p->dado <= 'z'){
			insere(adesivas,p->dado, &po);
			p = p->prox;
		}
	
		p = g->prim;
		nol *b = adesivas->prim;
	
		int cont=0;
		while (b != NULL){
			if (p->dado == b->dado)
				cont = cont+1;
			p = p->prox;
			b = b->prox;
			if (b == NULL || p == NULL || b->dado != p->dado)
				break;
		}
	
		if (cont == adesivas->tam){
			destroicadeia(adesivas);
			return 1;
		}
	
		destroicadeia(adesivas);
	}
	return 0;
}

/* retorna a cadeia com o maior tamanho */
cadeia* maiorSegmento(lista *t){
	cadeia *p = t->pri;
	cadeia *maior=t->pri;
	
	while (p != NULL){
		
		if (p->tam > maior->tam && p->info == 1)
			maior = p;
		p = p->proxima;
	}
	
	if (maior == t->pri)
		t->pri = maior->proxima;
		
	if (maior->info == 1){
		if (maior->proxima != NULL)
			maior->proxima->anterior = maior->anterior;
		
		if (maior->anterior != NULL)
		maior->anterior->proxima = maior->proxima;
	}
		
	return maior;

}

/* transforma as pontas adesivas e cegas em tipo normal */
void normaliza(cadeia *l){
	nol *k = l->prim;
	
	if (l->form == linear){
		while (k != NULL){
			if (k->dado >= 'a' && k->dado <= 'z'){
				k->dado = k->dado -32;
				k->tipob = normal;
			}
			k = k->prox;
		}
	}
	if (l->form == circular){
		while (k->prox != l->prim){
			if (k->dado >= 'a' && k->dado <= 'z'){
				k->dado = k->dado -32;
				k->tipob = normal;
			}
			k = k->prox;
		}
		if (k->dado >= 'a' && k->dado <= 'z'){
			k->dado = k->dado -32;
			k->tipob = normal;
		}
	}
}

/* processo de colagem utilizado para a primeira passagem, recebe 3 cadeias como argumentos */
/* cola em sequencia as cadeias "a", "b", "c" */
void colar(cadeia *a, cadeia *b, cadeia *c){
	a->info = 1;
	if (a->proxima == c){
		a->proxima = c->proxima;
		if (c->proxima != NULL)
			c->proxima->anterior = a;
	}
	else{
		c->anterior->proxima = c->proxima;
		if (c->proxima != NULL)
			c->proxima->anterior = c->anterior;
	}
		
	if (b->proxima != NULL)
		b->proxima->anterior = b->anterior;

	if (b->anterior != NULL)
		b->anterior->proxima = b->proxima;
		
	normaliza(b);
	normaliza(c);
	if (a->ult->dado >= 'a' && a->ult->dado <= 'z')
		a->ult->dado = a->ult->dado -32;
	a->ult->prox = b->prim;
	b->ult->prox = c->prim;
	a->ult = c->ult;
	if (a->ult->dado >= 'A' && a->ult->dado <= 'Z')
		a->ult->dado = a->ult->dado +32;
	
	reindexa(a);
	a->tam = a->ult->pos;
	free(b);
	free(c);
	
}

/* processo de colagem utilizado na segunda passagem */
/* cola em sequencia as cadeias "a" e "b" */
void colar2(cadeia *a, cadeia *b){
	nol *p = a->ult;
	
	if (b->proxima != NULL)
		b->proxima->anterior = b->anterior;

	if (b->anterior != NULL)
		b->anterior->proxima = b->proxima;
	
	
	p->prox = b->prim;
	b->prim->ant = p;
	a->ult = b->ult;
	a->ult->prox = a->prim;
	a->prim->ant = a->ult;
	
	free(b);
	a->form = circular;
	
	reindexa(a);
	a->tam = a->ult->pos;
	normaliza(a);
	
}

/* funçao principal da funçao glue*/
/* faz os laços que andam pelas cadeias e utiliza das funções de verificação*/
/* faz uma primeira passagem para a colagem de segmentos par a par*/
/* e uma segunda passagem de segmento a segmento caso sobre segmentos na lista "dois" */
void glue(lista *um, lista *dois){
	
	/* Primeira passagem */
	cadeia *k = dois->pri;
	cadeia *atual1;
	cadeia *atual2;
	cadeia *debug;
	int cont = 0;
	
	/* o primeiro while representa o andamento nos segmento de "dna2.txt" */
	/* obs o campo "info" na estrutura das cadeias foi criado apenas para o programa */
	/* saber diferenciar quais cadeias estao disponivel ou nao na primeira passagem */
	/* obviamente durante a leitura, todos os segmentos recebem "info = 0" */
	while (k != NULL){
		atual1 = um->pri;
		while (atual1->info != 0){ 
			atual1 = atual1->proxima;
			if (atual1 == NULL)
				break;
		}
		
		if (atual1 == NULL)
			break;
			
		atual2 = atual1->proxima;
		while (atual2->info != 0){ 
			atual2 = atual2->proxima;
			if (atual2 == NULL)
				break;
		}
		
		if (atual2 == NULL)
			break;
		
		/* este laço anda de par a par os segmentos de dna1.txt */
		/* o andamento é feito do seguinte modo: s1,s2 ; s1,s3; ...; sn, sm; */
		while (atual1 != NULL && atual2 != NULL){
			debug = atual2->proxima;
			while (atual2 != NULL){
				
				/* tenta fazer a colagem na ordem si, sk, sj */
				if (compCega(atual1, k) && compAdesiva(atual2,k)){
				
					if (k == dois->pri)
						dois->pri = k->proxima;
				
					colar(atual1, k, atual2);
					
					k = dois->pri;
					if (k != NULL){
						while (k->proxima != NULL){ k = k->proxima;}
					}
					dois->ulti = k;
				
					break;
				}
				else{
					/* tenta fazer a colagem na ordem sj, sk, si */
					if (compCega(atual2, k) && compAdesiva(atual1,k)){
						
						if (k == dois->pri)
							dois->pri = k->proxima;
							
						if (atual1 == um->pri)
							um->pri = atual2;
						
						invertecadeias(atual1, atual2);
						
						colar(atual2, k, atual1);
						atual1 = atual2;
						
						cadeia *laco = um->pri;
						while (laco->proxima != NULL){
							laco = laco->proxima;
						}
						
						um->ulti = laco;
						
						k = dois->pri;
						if (k != NULL){
							while (k->proxima != NULL){ k = k->proxima;}
						}
						dois->ulti = k;
				
						break;
					}
					else{
						/* tenta a proxima combinaçao*/
						/* ex: estava em s1, k, s2, agora o proximo teste sera s1, k , s3 */
						atual2 = debug;
						if (atual2 != NULL){
							while (atual2->info != 0){ 
								atual2 = atual2->proxima;
								if (atual2 == NULL)
									break;
							}
						}
						
						if (atual2 == NULL)
							break;
						debug = atual2->proxima;
						}
				}
			}
			/* neste pedaço tenta o proximo pivo de combinaçao*/
			/* ex: estava em s1, k, s(2 - m), agora o proximo teste sera s2, k , s(3 - m) */
			if (atual2 == NULL)
				break;
				
			if (atual1->info == 1)
				atual1 = atual1->proxima;
			
			if(atual1 != NULL)
				atual2 = atual1->proxima;
			else
				atual2 = NULL;
			k = dois->pri;
			if (k == NULL)
				break;
		}
	if (k != NULL)
		k = k->proxima;
	}
					
	/* Segunda passagem */
	/* neste pedaço os testes serao de segmento a segmento*/
	/* a ordem de testes combinatorios a serem feitos é k(1-n), s(1-n) */
	cadeia *b;
	int ver = 0;
	if (dois->pri != NULL){
		k = dois->pri;
		
		while (k != NULL){
			atual1 = um->pri;
			while (atual1 != NULL){
				
				if (atual1->form != circular){
					if (compAdesiva(atual1, k) && compCega(atual1, k)){
						b = k;
						k = k->proxima;
						if (b == dois->pri)
							dois->pri = b->proxima;
						
						colar2(atual1, b);
						ver = 1;
					
						b = dois->pri;
						if (b != NULL){
							while (b->proxima != NULL){
								b = b->proxima;
							}
						}
						dois->ulti = k;
						printf ("cadeia circular criada\n");
					}
				}
				atual1 = atual1->proxima;
				if (k == NULL)
					break;
			}
		if (k != NULL)
			k = k->proxima;
		}
	}
	if (ver == 0)
		printf ("Nenhuma cadeia circular criada\n");
}

