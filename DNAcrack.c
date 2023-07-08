#include <stdio.h>
#include "listas.h"
#include "analyze.h"
#include "cut.h"
#include <string.h>
#include "glue.h"
#include "recombine.h"

/*codigo principal, que faz a chamada das funçoes "-analyze" ,"-cut" e "-glue" */
int main(int argc, char **argv){
	FILE *arq1, *arq2, *arq3;
	
	/* funçao -analyze */
	if (strcmp(argv[1],"-analyze") == 0){
		arq1 = fopen(argv[2], "r");
		arq2 = fopen(argv[3], "r");
		if (verificacao(arq1,arq2)){
			rewind (arq1);
			rewind (arq2);
			leitura(arq1,arq2);
			}
		else
			printf ("Arquivo vazio ou invalido\n");
	}
	
	/* funçao -cut */
	if (strcmp(argv[1],"-cut") == 0){
		
		if (strcmp(argv[2],"-l") == 0){
				arq1 = fopen(argv[3], "r");
				arq2 = fopen(argv[4], "r");
				if (verific(arq1,arq2)){
					int ehcircular = 0;
					cadeia *l = cria();
					lista *g = crea();
					avalia(g,l,arq1,ehcircular);
					int tamanho = tam(arq2);
					corte(g,arq2,tamanho);
					impr(g);
				}
				else
					printf ("Arquivo vazio ou invalido\n");
		}
	}

	/* funçao -glue */
	if (strcmp(argv[1],"-glue") == 0){
		
		if (strcmp(argv[2], "-l") == 0){
			arq1 = fopen(argv[3], "r");
			arq2 = fopen(argv[4], "r");
			int ehcircular = 0;
			cadeia *a = cria();
			cadeia *b = cria();
			lista *um = crea();
			lista *dois = crea();
			avalia(um,a,arq1,ehcircular);
			avalia(dois,b,arq2,ehcircular);
			glue(um,dois);
			cadeia *maior = maiorSegmento(um);
			if (maior->info == 1)
				imprGlueApenasCadeia(maior);
			imprGlue(um,dois);
			
		}
	}
	
	/* funçao -recombine */
	if (strcmp(argv[1],"-recombine") == 0){
		
		if (strcmp(argv[2], "-c") == 0){
			arq1 = fopen(argv[3], "r");
			arq2 = fopen(argv[4], "r");
			arq3 = fopen(argv[5], "r");
			cadeia *a = cria();
			cadeia *b = cria();
			lista *um = crea();
			lista *dois = crea();
			avalia(um,a,arq1,1);
			avalia(dois,b,arq2,0);
			int tamanho = tam(arq3);
			cortaCircular(um, um->pri,tamanho, arq3);
			corte(dois,arq3,tamanho);
			int verifica;
			cadeia *recombined = colarRecombine(um,dois,&verifica);
			if (verifica == 1)
				imprRecombinecadeia(recombined);
			if (verifica == 0)
				imprRecombinefail(um);
		}
	}
}
