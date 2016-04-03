#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define T 100

typedef struct {
	char ** string;
	int qtd;
}lista_string;

lista_string* criaLista(int cap) {
	lista_string *eLS = (lista_string*) calloc (1,sizeof(lista_string));
	eLS->string = (char**) calloc (cap,sizeof(char**));
	eLS->qtd = cap;
	return eLS;
}

int contaLinha(FILE *fp) {
	int nroLinhas = 0;
	char str[30];
	while(!feof(fp)) {
		fgets(str,30,fp);
		nroLinhas++;
	}
	return nroLinhas;
}

int inserirLista(lista_string *l, char *s, int index) {
	int tam = strlen(s)+1;
	l->string[index] = (char*) calloc (tam,sizeof(char));
	strcpy(l->string[index],s);
	return 0;
}

lista_string *importar(FILE * fp, lista_string *l) {
	int i=0, j=0, t;
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
	int i=0;
	for (i=0 ; i< l->qtd ; i++) {
		printf ("STRING (%d):  %s\n", i, l->string[i]);
	}
}

lista_string *listaEstados(lista_string * l, int index) {
	int tam = strlen(l->string[index])+1;
	char * str = (char*) calloc (tam,sizeof(char));
	strcpy(str,l->string[index]);
	str[tam] = '\0';
	
	int contEspacos=0;
	int i=0;
	char c = str[i];
	while(c != '\0') {
		c = str[i];
		if(c ==' ') {
			contEspacos++;
		}
		c = str[i++];
	}
	
	lista_string * l1 = criaLista(contEspacos+1);
	char * pch;
	pch = strtok(str," ");
	i = 0;
	while(pch != NULL) {
		inserirLista(l1,pch,i);
		pch = strtok(NULL," ");
		i++;
	}
	return l1;
}


int main() {
	int cap;
	FILE *fp;
	fp = fopen("modelo_2.txt","r");
	if (!fp) {
		printf ("Erro na abertura do arquivo!\n");
		exit(1);
	}
	cap = contaLinha(fp);
	lista_string * lista = criaLista(cap);
	fp = fopen("modelo_2.txt","r");
	lista = importar(fp, lista);
	imprime(lista);
	lista_string * listaE = listaEstados(lista, 0);
	imprime(listaE);
	return 0;
}
