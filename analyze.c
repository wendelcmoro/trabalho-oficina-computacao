#include <stdio.h>

/* as funçoes desse arquivo sao de uso exclusivo da funçao "-analyze" */

/* funçao que apenas avalia a integridade dos arquivos */
/* retorna 0 se houver algum char que nao eh base ou arquivo nulo, ou retorna 1 se tiver ok */
int verificacao(FILE *gene, FILE *prot){
	char c = fgetc(gene);
	int ver = 0;
	
	if (gene == NULL || prot == NULL)
		return 0;
		
	while (c != EOF){
		if (c != 'A' && c != 'C' && c != 'G' && c != 'T')
			ver = ver+1;
		c = fgetc(gene);
	}

	if (ver > 1)
		return 0;
	return 1;
}

int compara(char base[3], char gene[3]){
	int cont=0;
	for (int i = 0; i <= 2; i++)
		if (base[i] == gene[i])
			cont = cont+1;
	if (cont == 3)
		return (1);
	else
		return (0);
}

void imprimebase(int y, char base[10000], char prot[10000], int letras){
	char bas[5] = {'A', 'C', 'T', 'G', '\0' }; /* contem as bases para a impressao e geraçao na tela */
	char c[3]; /* "c" sera o vetor que armanezara a base gerada */
	char bm[3]; /* "bm" sera o vetor que armanezara de 3 em 3 as bases de uma proteina recebida da funçao "match" */
	int a = -1; /* "a" auxilia na contagem de 3 em 3 para a impressao e comparaçao da proteina */
	int cont = 1; /* auxilia na verificaçao do vetor "prot" para o valor de qual a proteina a ser imprimida */ 
	int debug = 0; /* apenas indica se a comparaçao de "c" atual retornou verdadeiro ou falso, se for falso imprime "." */
	int o = 0; /* "o" auxilia na contagem de bases imprimidas, caso chegue a 3, pula a linha e começa a impressao na prox. linha */
	
	/* laço de geração da base(por ex:i=0, j=0, z=0 gerarão a base "AAA" para a comparaçao) */
	for (int i = 0; i <= 3; i++){
		for (int j = 0; j <= 3; j++)
			for (int z = 0; z <= 3; z++){
				c[0] = bas[i];
				c[1] = bas[j];
				c[2] = bas[z];

				/* laço para a impressao da base gerada na tela */
				for (int s = 0; s <= 2; s++)
						printf ("%c", c[s]);
				printf (" ");
				o = o+1;

				/* faz a copia a partir da posiçao "y" de "base" de 3 em 3 para o vetor "bm" */
				/* a ira contar de 3 em 3, e se chegou em 3, compara "bm" com a base gerada em "c" */ 
				for (int t = y; t <= (y + (letras*3) - 1); t++){ 
					a = a+1;
					bm[a] = base[t];	

					/* se a contou 3 bases */
					if (a == 2){
							/* compara "c" atual com "bm" atual */
							/* se forem iguais imprime a proteina correspondente do incide "cont" */
							if (compara(bm,c) == 1 && debug == 0){
								printf ("%c	", prot[cont]);
								debug = 1;
							}
						/* a cada geraçao de "bm", cont avançara para a proxima proteina */
						cont = cont+1;
						/* caso ultrapasse, cont apenas recomeçara de 1 para a proxima geraçao de "c" */
						if (cont > letras)
							cont = 1;
						a = -1;
					}
				}


				if (debug == 0)
					printf (".	");

				if (debug == 1)
					debug = 0;

				if (o == 4){
					printf ("\n");
					o = 0;
				}
			}
	}
}

/*funçao que faz a avaliaçao das bases em relaçao a proteina e verifica se há um casamento*/
void match(char gene[10000], char prot[10000], int letras, int k){
	int p, a, b, c, r, l;
	/* "c" e "b" sao variaveis auxiliares para comparaçao de x */
	/* "p" auxilia na comparaçao das proteinas, "l" auxilia p em caso de repetições */
	
	a = 2;/*"a" representa o nosso limitador de proteinas*/
		/*caso a verificaçao varra o gene todo e encontre o casamento, "a" tera o tamanho da proteina*/
	
	int x = 1;/*representa qual a posiçao que se iniciara a comparaçao(por ex: ATGCTG*/ 
		/*iniciara em x=A, posteriormente passara para x=C, e assim em diante*/
	
	int y = x;/*"y" diferentemente de "x", sera um variavel de incremento em 1*/
			/*por ex: caso o gene ACTGGT, y=A inicialmente, posteriomente marcara C e assim em diante*/
			
			/*"y" é tambem uma referencia para o valor inicial de "x" em uma nova verificação*/
			/*por ex: "x" avança de 3 em 3, "y" de 1 em 1, caso estejamos na posiçao 10 de verificação e x=10 e nao houve casamento*/
			/*y=1 sera y=2, e "x" recebera o valor de "y" e recomeçara uma verificaçao dessa posiçao e caso ocorra casamento*/
			/*"y" tambem sera a variavel que representara a posiçao incial do casamento*/
			
			
	b = x+3; /*b apenas representa a posiçao que iniciara a comparaçao(por ex: na base ACTGCC, se x=A, entao b=G)*/
		   /*obs: b apenas auxilia na comparaçao do gene*/

	/*laço que compara letra a letra o vetor das proteinas com o vetor de gene*/
	while (1){
		p = a; /* "p" auxiliara na contagem das proteinas dentro do laço while*/
		l = p; /* "l" apenas sera um auxiliar de "p" no caso de ocorrer proteinas iguais */

			while (p <= letras){
				c = x;
				
				/* laço que verifica repetiçoes*/
				for (int i = b; i <= b+2; i++){/* ate b+2 porque representa o tamanho 3 */
					if (gene[c] == gene[i])  /* por ex AGT, b=A incialmente, entao b+2=T */
						r = r+1; /* verifica a quantidade de vezes que uma base repetiu */
					c = c+1; /* "c" recebe o valor de "x" ate 2 posiçoes a frente */
				}
				
				l = l+1;
				
		/* vericaçao se as bases de uma proteina sao iguais a outra, caso nao sejam, a comparaçao começa na proxima posiçao de "x" */
				if (r == 3){
					if (prot[a-1] != prot[l-1]){
						r = 0;
						break;
					}
				}
		/* caso sejam a mesma proteina, a verificaçao continua */
				else{
					r = 0;
					b = b+3;
					p = p+1;
					l = p;
				}
			}
		
		/* a partir daqui há uma verificaçao de o gene todo foi varrido ou se é necessario varrer uma posiçao adiante */
		p = p-1;
		
		/* se "p" comparou todas a proteina atual com todas as outras proteinas, a verificaçao vai para a proxima proteina*/
		if (p == letras){
			a = a+1;
			x = x+3;
			b = x+3;
		}
		/* caso "p" deixou de comparar alguma proteina por haver repetição */
		else{
			/*caso as proteinas tenham sido todas comparadas, a posiçao de comparaçao avança em 1 o indice de "y" */
			/*e a verificação recomeça*/
			if (a < letras){
				a = 2;
				y = y+1;
				x = y;
				b = x+3;
			}
			else{
				/* caso a comparação termine e y tenha passado do tamanho do gene */
					if (y > k){
						printf ("nenhum casamento encontrado \n");
						break;
					}
				/* caso a comparaçao termine e teve uma contagem correta */
				/* tambem faz a chamada para a impressao dos casamentos ocorridos */
					else{
						printf ("casamento encontrado na posiçao %d\n", y-1);
						imprimebase(y,gene,prot,letras);
					break;
					}
				}
			}
	}
}

/*faz a leitura das bases e da proteina, e tambem define o tamanho da proteina*/
void leitura(FILE *gene, FILE *prot){
	int cont = 0; int i = 1; int j = 1;
	char bs[10000];/*vetor que armanezara as bases (A,C,T,G)*/
	char am[10000];/*vetor que armanezara a proteina (a-z)*/
	bs[i] = fgetc(gene);
	int letras;

	/*faz a transferencia do arquivo gene para um vetor*/
	while ((bs[i]) != EOF){
		i = i+1;
		(bs[i]) = fgetc(gene);
	}
	
	fclose(gene);
	int k = i-1; /*a variavel "k", representa o tamanho do gene*/
	i = 1;	
	letras = 0;
	am[i] = fgetc(prot);

	/*faz a contagem do tamanho da proteina e joga em um vetor*/
	while (am[i] != EOF){
		i = i+1;
		letras = letras+1;
		am[i] = fgetc(prot);
	}
	
	/*a variavel "letras" representa o tamanho da proteina*/
	letras = letras-1;
	fclose(prot);
	
	match(bs,am,letras,k);
}
