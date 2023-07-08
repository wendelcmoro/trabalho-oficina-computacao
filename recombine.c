#include <stdio.h>
#include <stdlib.h>
#include "listas.h"
#include "cut.h"
#include "glue.h"

/*adaptçao da função "corte" do comando "-cut" para os propositos do recombine na cadeia circular */
void cortaCircular(lista *um, cadeia *l,int tamenz, FILE *enzima){
		int po = 0;
		if (encontra(l,enzima,tamenz,&po) == 1)
			separa(l,po,tamenz);
		um->ulti = um->pri->proxima;
}


/*adaptçao da função "glue" do comando "-glue" para os propositos do recombine na cadeia circular */
cadeia* colarRecombine(lista *um, lista*dois, int *verifica){
	cadeia *k = dois->pri;
	cadeia *atual1 = um->pri;
	cadeia *atual2 = atual1->proxima;
	
	while (k != NULL){
		if (compCega(atual1, k) && compAdesiva(atual2,k)){
			atual1->anterior = NULL;
			atual1->ult->prox = k->prim;
			k->ult->prox = atual2->prim;
			atual1->ult = atual2->ult;
			atual1->prim->ant = atual1->ult;
			atual1->ult->prox = atual1->prim;
			atual2->proxima = NULL;
			free(atual2);
			free(k);
			atual1->form = circular;
			*verifica = 1;
			return atual1;
			break;
		}
		else{
			if (k != NULL)
				k = k->proxima;
			
			if (k == NULL)
				break;
		}
	}
	*verifica = 0;
}
