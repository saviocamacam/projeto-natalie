#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define T 100

typedef struct {
	char **string;
	int qtd;
}lista_string;

int contaLinha(FILE *fp) {
	int nroLinhas = 0;
	char str[30];
	while(!feof(fp)) {
		fgets(str,30,fp);
		nroLinhas++;
	}
//	rewind(fp);
	return nroLinhas;
}

int inserirLista(lista_string *l, char *s, int index) {
	int tam = strlen(s);
	l->string[index] = (char*) calloc (tam,sizeof(char));
	strcpy(l->string[index],s);
	return 0;
}

lista_string * criaLista(int cap) {
	lista_string *eLS = (lista_string*) calloc (1,sizeof(lista_string));
	eLS->string = (char**) calloc (cap,sizeof(char**));
	eLS->qtd = cap;
	return eLS;
}

lista_string *importar(FILE * fp, lista_string *l) {
	int i=0, j=0, t;
	char c;
	char copia[T];	
	while(!feof(fp)) {
		fgets(copia,100,fp);
		t = strlen(copia);
		for (i=0 ; i<t ; i++) {
			if (copia[i] == '\n') {
				copia[i] = '\0';
			}
		}
		inserirLista(l,copia, j);
		j++;
	}
	fclose(fp);
	return l;
}

void imprime (lista_string *l) {
	int i;
	for (i=0 ; i< l->qtd ; i++) {
		printf ("STRING (%d):  %s\n", i, l->string[i]);
	}
}


Alfabeto* newAlfabeto(char* c)
{
	Alfabeto* alf;

	alf = (Alfabeto*) malloc(sizeof(Alfabeto));
	alf->alfabetotam = (strlen(c)/2);
	strcpy(alf->alfabeto, c);
	
	return(alf);
}
int main(int argc, char *argv[]) {
	int n;//alfabeto
	int cap;
	FILE *fp;
	fp = fopen("modelo_2.txt","r");
	if (fp == NULL) {
		printf ("Erro na abertura do arquivo!\n");
		exit(1);
	}
	cap = contaLinha(fp);
	lista_string * lista = criaLista(cap);
	rewind(fp);
	lista = importar(fp, lista);
	imprime(lista);
	

	Alfabeto* a;
	a = newAlfabeto(lista_string[qtd]);
	

	return 0;
}
