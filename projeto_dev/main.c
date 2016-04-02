#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char **string;
}lista_string;

int contaLinha(FILE *fp) {
	int nroLinhas = 0;
	while(!feof(fp)) {
		nroLinhas++;
	}
	return nroLinhas;
}

int inserirLista(lista_string *l, char *s, int index) {
	int tam = strlen(s);
	l->string[index] = (char*) calloc (tam,sizeof(char));
	strcpy(l->string[index],p);
	return 0;
}

lista_string * criaLista(int cap) {
	lista_string *eLS = (lista_string*) calloc (1,sizeof(lista_string));
	eLS->string = (char**) calloc (cap,sizeof(char**));
	return eLS;
}

lista_string importar(FILE * fp, lista_string *l) {
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
	remove_indice(l,(l->qtd-1));
	return l;
}

void imprime (lista_string *l) {
	int i;
	for (i=0 ; i< l->qtd ; i++) {
		printf ("STRING (%d):  %s\n", i, l->string[i]);
	}
}

int main(int argc, char *argv[]) {
	int cap;
	FILE *fp;
	fp = fopen("modelo_2.txt","r");
	if (!fp) {
		printf ("Erro na abertura do arquivo!\n");
		exit(1);
	}
	fp = fopen("modelo1.txt","r");
	cap = contaLinha(fp);
	lista_string * lista = criaLista(cap);
	lista = importar(lista);
	imprime(lista);
	return 0;
}
