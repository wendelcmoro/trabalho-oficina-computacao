#ifndef _analyze_
#define _analyze_

void leitura(FILE *gene, FILE *prot);
void match(char base[10000],char prot[10000], int letras, int k);
void imprimebase(int y, char base[10000], char prot[10000], int letras);
int compara(char base[3],char gene[3]);
int verificacao(FILE *gene, FILE *prot);


#endif
