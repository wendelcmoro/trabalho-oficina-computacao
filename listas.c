#include <stdio.h>
#include <stdlib.h>
#include "listas.h"

/*cria um novo tipo cadeia*/
cadeia* cria(){
	cadeia *x = malloc(sizeof(cadeia));
	x->prim = NULL;
	x->ult = NULL;
	return x;
}

/*cria um novo tipo lista*/
lista* crea(){
	lista *x = malloc(sizeof(lista));
	x->pri = NULL;
	x->ulti = NULL;
	return x;
}

/*faz a ligaçao dos ponteiros da lista com a primeira cadeia criada*/
void liga(lista *g, cadeia *l){
	if (g->pri == NULL){
		g->pri = l;
		g->pri->proxima = NULL;
		g->pri->anterior = NULL;
	}
}

/*diferente da funçao liga que apenas manipula a primeira cadeia,*/ 
/* esta funçao aloca a memoria para a criaçao de uma nova cadeia sendo lida*/
void apontanovacadeia(cadeia *k, lista *g){
	cadeia *m=cria();
	m->proxima = NULL;
	m->info = 0;
	m->anterior = k;
	k->proxima = m;
	g->ulti = m;
}

/*adiciona novos elementos a uma cadeia*/
void insere(cadeia* l, char i, int *po){
	if (l->prim == NULL){
		*po = *po+1;
		l->ult = l->prim = malloc(sizeof(nol));
		l->prim->dado = i;
		
		if (i >= 'a' && i <= 'z')
			l->prim->tipob = adesiva;
		else
			l->prim->tipob = normal;
			
		l->prim->pos = *po;
		l->proxima = NULL;
		
		if (l->form == circular){
			l->prim->prox = l->prim;
			l->prim->ant = l->prim;
			return;
		}
		
		l->prim->prox = NULL;
		l->prim->ant = NULL;
		l->tam = 1;
		return;
	}
	*po = *po+1;
	
	nol *new = malloc(sizeof(nol));
	nol *p = l->prim;
	
	if (l->form == circular){
		while (p->prox != l->ult){
			p = p->prox;
		}
		if (p->prox == l->ult)
			p = p->prox;
	}
	else{
		while (p->prox != NULL){
			p = p->prox;
		}
	}
	new->dado = i;
	new->pos = *po;
	new->ant = p;
	l->tam = l->tam+1;
	
	if (l->form == circular){
		new->prox = l->prim;
		l->prim->ant = new;
	}
	else
		new->prox = NULL;
		
	p->prox = new;
	l->ult->tipob = normal;
	l->ult = new;
	if (l->ult->dado >= 'a' && l->ult->dado <= 'z')
		l->ult->tipob = cega;
}

/*faz a impressao na tela e joga todas as listas de cadeias em um arquivo de saida*/
/*de nome "saida.txt"*/
void impr(lista *g){
	FILE *saida;
	saida = fopen("saida.txt", "w");
	int i = 1;
	cadeia *k = g->pri;
	
	while (k != NULL){
		nol *p = k->prim;
		if (k->form == linear){
			
			while (p != NULL){
				fputc(p->dado,saida);
				p = p->prox;
			}
		}
		else{
			
			while (p->prox != k->prim){
				fputc(p->dado,saida);
				p = p->prox;
			}
			
			if (p == k->ult)
				fputc(p->dado,saida);
		}
		if (k->proxima != NULL)
			fputc(' ',saida);
		i = i+1;
		k = k->proxima;
	}
	fclose(saida);
}

/* desaloca o espaço de uma cadeia */
/* utilizada principalmente pela funçao "compAdesiva" */
void destroicadeia(cadeia *l){
		
	nol *atual = l->prim;
	nol *ant;
	
	while (atual != NULL){
		ant = atual;
		atual =  atual->prox;
		free (ant);
	}
	
	free(l);
}

/* utilizada pela segunda passagem da funçao glue */
/* apenas troca as posiçoes das cadeia l e b em uma lista */
void invertecadeias(cadeia *l, cadeia *b){
	
	if (l->proxima != b){
		cadeia *t = l->proxima;
		cadeia *y = l->anterior;
		cadeia *r = b->proxima;
		cadeia *q = b->anterior;
	
		l->proxima = r;
		if (r != NULL)
			r->anterior = l;
		l->anterior = q;
		if (q != NULL)
			q->proxima = l;
		b->proxima = t;
		b->anterior = y;
	}
	
	if (l->proxima == b){
		cadeia *t = b->proxima;
		cadeia *y = l->anterior;
		
		b->anterior = y;
		l->proxima = t;
		l->anterior = b;
		b->proxima = l;
		
		if (y != NULL)
			y->proxima = b;
		if (t != NULL)
			t->anterior = l;
	}
}

/* funçao de impressao exclusiva de "-glue" */
void imprGlue(lista *l, lista *g){
	FILE *saida;
	saida = fopen ("dump.txt", "w");
	if (l->pri != NULL){
		cadeia *k= l->pri;
		while (k != NULL){
			nol *p = k->prim;
		
			if (k->form == linear){
				while (p != NULL){
					fputc(p->dado,saida);
					p = p->prox;
				}
			}
		
			if (k->form == circular){
				while (p->prox != k->prim){
					fputc(p->dado,saida);
					p = p->prox;
				}
				fputc(p->dado,saida);
			}
			fputc(' ',saida);
			k = k->proxima;
		}
	}
	if (g->pri != NULL){

		cadeia *k= g->pri;
		while (k != NULL){
			nol *p = k->prim;
		
			if (k->form == linear){
				while (p != NULL){
					fputc(p->dado,saida);
					p = p->prox;
				}
			}
		
			if (k->form == circular){
				while (p->prox != k->prim){
					fputc(p->dado,saida);
					p = p->prox;
				}
				fputc(p->dado,saida);
			}
			fputc(' ',saida);
			k = k->proxima;
		}
	}
	fclose (saida);
}

/* esta funçao recebe como argumento apenas uma cadeia */
/* utilizada apenas para imprimir o maior segmento de uma lista, ate agr usada apenas pela funçao "-glue" */
void imprGlueApenasCadeia(cadeia *l){
	FILE *saida;
	saida = fopen ("output.txt", "w");
	if (l->prim != NULL){
		nol *k = l->prim;
		if (l->form == linear){
			while (k != NULL){
				fputc(k->dado,saida);
				k = k->prox;
			}
		}
		if (l->form == circular){
			while (k->prox != l->prim){;
				fputc(k->dado,saida);
				k = k->prox;
			}
			fputc(k->dado,saida);
		}
	}
	fclose (saida);
}

/*redefine o tamanho da cadeia e do segmento criado no campo "tam"*/
void reescalona(cadeia *l, cadeia *x){
	l->tam = l->ult->pos;
	
	if ((x->ult->dado >= 'a' && x->ult->dado <= 'z') || (x->ult->dado >= 'A' && x->ult->dado <= 'Z'))
		x->tam = x->ult->pos;
	else{
		nol *o = x->ult;
		o = o->ant;
		x->tam = o->pos;
	}
}

/*reindexa o campo "pos" do nó da cadeia, que indica qual a posiçao de cada elemento dentro de uma cadeia*/
void reindexa(cadeia *l){
	nol *x = l->prim;
	int i = 1;
	
	if (l->form == linear){
		
		while (x != NULL){
			x->pos = i;
			i = i+1;
			x = x->prox;
		}
		
	}
	else{
		
		while (x->prox != l->prim){
			x->pos = i;
			i = i+1;
			x = x->prox;
		}
		
		x->pos = i;
	}
}

/*funçao que faz a leitura da entrada e avalia a criaçao de novas cadeias, verifica se há espaços no arquivo de entrada durante a leitura*/
/*e caso haja espaço, faz a criaçao de uma nova cadeia usando a funçao "apontanovacadeia"*/
void avalia(lista *g, cadeia *l, FILE *DNA, int ehcircular){
	int po = 0;
	liga (g,l);
	cadeia *k = g->pri;
	
	if (ehcircular == 1)
		k->form = circular;
	else
		k->form = linear;
		
	k->info = 0;
	char c = fgetc(DNA);
	
	while (c != EOF){
		if (c == ' '){
			c = fgetc(DNA);
			po = 0;
			apontanovacadeia(k,g);
			k = k->proxima;
			
			if (ehcircular == 1)
				k->form = circular;
			else
				k->form = linear;
				
			insere(k, c, &po);
		}
		else
			insere(k,c, &po);
		c = fgetc(DNA);
	}
	
	free(k->ult);
	k->ult = k->ult->ant;
	
	if (k->form == circular){
		k->ult->prox = k->prim;
		k->prim->ant = k->ult;
	}
	
	else
		k->ult->prox = NULL;
	k->tam = k->tam-1;
}

void imprRecombinecadeia(cadeia *l){
	FILE *saida;
	saida = fopen ("recombined.txt", "w");
	nol *aux = l->prim;
	while (aux->prox != l->prim){;
		if (aux->dado >= 'A' && aux->dado <= 'Z')
			fputc(aux->dado,saida);
		if (aux->dado >= 'a' && aux->dado <= 'z')
			fputc(aux->dado-32,saida);
		aux = aux->prox;
	}

	if (aux->dado >= 'A' && aux->dado <= 'Z')
		fputc(aux->dado,saida);
	if (aux->dado >= 'a' && aux->dado <= 'z')
		fputc(aux->dado-32,saida);
	
	fclose(saida);
}

void imprRecombinefail(lista *g){
	FILE *saida;
	saida = fopen("recombined.txt", "w");
	cadeia *k = g->pri;
	nol *aux;
	while (k != NULL){
		aux = k->prim;
		while (aux != NULL){
			printf ("%c", aux->dado);
			if (aux->dado >= 'A' && aux->dado <= 'Z')
				fputc(aux->dado,saida);
			if (aux->dado >= 'a' && aux->dado <= 'z')
				fputc(aux->dado-32,saida);
			aux = aux->prox;
		}
		k = k->proxima;
	};
	fclose(saida);
}
