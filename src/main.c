#include "../lib/mapa.h"
#define T 100

bool verficador(Mapa* m)
{
	int i;

	for (i=0; i<m->n; i++)
	{
		if(m->state[i] == true)
		{
			return(true);
		}
	}

	return(false);
}

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

			if (copia[i] == 13) //corrigindo bug
			{
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
	//printf("quantidade de espaços %d\n", contEspacos);
	lista_string * l1 = criaLista(contEspacos+1);
	char * pch;
	pch = strtok(str," \0");
	i = 0;
	//	char v[]="0\0"; int m;
	while(pch != NULL) {
		/*		printf("valor pch ->>>>>>>>>>>%s\nvalor while ->>>>>>>>>>>>>>>>> %d\n",pch, strcmp(pch,v));
				for(m=0; m<strlen(pch); m++)
				{
				printf("//////////%d, %c/////////\n",strlen(pch), pch[m]);
				} LOUCURA MODE*/
		inserirLista(l1,pch,i);
		pch = strtok(NULL," ");
		i++;
	}
	//inserirLista(l1,'\0', i);
	//	l1->qtd--;
	return l1;
}

void addNos(lista_string* l, Mapa* m)
{
	int i,j, k, z;
	lista_string* aux;

	for (i=4; i<l->qtd; i++)
	{
		aux = listaEstados(l,i);
		bool verif = true;
		for (j=0; j<m->alf->qtd; j++)
		{
			//	printf("%s, %s, %d, %d\n", aux->string[1], m->alf->string[j], strcmp(aux->string[1], m->alf->string[j]), m->alf->qtd);
			if (!strcmp(aux->string[1], m->alf->string[j]))
			{
				verif = false;
			}
		}

		if(verif)
		{
			printf("Erro alfabeto\n");
			exit(0);
		}
		//printf("\n\n\n\n");
		for (k=0; k<m->n; k++)
		{
			if (!strcmp(aux->string[0],m->labels[k]))
			{
				for (z=0; z<m->n; z++)
				{
					if (!strcmp(aux->string[2],m->labels[z]))
					{	
//						printf("foi adicionado, or:%d des:%d va:%s %d\n", k,z,aux->string[1], m->n);

						addAresta(m,k,z,aux->string[1][0]);
//printMapa(m);
					}
				}
			}

		}


	}
}

////////////////////////////
void episilon(Mapa* m)
{
	int or, de;
	bool ver = false;
	
			for(or=0; or<m->n; or++)
			{

				for (de=0; de<m->n; de++)
				{
					if ((isArestaVal(m,or,de,'B')) && (m->state[de] == false) && (m->state[or]))
					{
						m->state[de] = true;
						ver=true;
					}
				}
			}
	if (ver)
	{
		ver = false;
		episilon(m);
	}
}



bool processoFinal(Mapa* m, char* argv)
{	
	int tam, i, j, k, z;
	bool modf[m->n];

	tam = strlen(argv);

	for (i=0; i<m->n; i++)
	{
		modf[i] = false;	
	}

	

		for (i=0; i<tam; i++)
		{

			for(j=0; j<m->n; j++)
			{
				if (m->state[j])
				{
					for(k=0; k<m->n; k++)
					{
						if (isArestaVal(m,j,k,argv[i]))
						{
							if(argv[i] == 'B' )
							{
								modf[j] = true;
							}
							modf[k] = true;
						}

					}
				}
			}

			for (z=0; z<m->n; z++) //estado atual
			{
				m->state[z] = modf[z];
				modf[z] = false;	
			}
			episilon(m);
		}
		for (i=0; i<m->n; i++)
		{		
			if(m->state[i])
				{//printf("Está aqui %d\n", i);
				if (m->type[i] == 1)
				{	
							return(true);
				}
			}
		}

	

	return(false);
}

int main(int argc, char* argv[]) {
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
//	imprime(lista);
	lista_string* alfabeto = listaEstados(lista, 0);
	lista_string* estados = listaEstados(lista, 1);
	lista_string* iniciais = listaEstados(lista, 2);
	lista_string* finais = listaEstados(lista,3);



	//alfabeto->string[1][1] = '\0';
	//while(p != 13)
	{
		//	ind++;
		//	p = alfabeto->string[1][ind];
	}
	//alfabeto->string[1][ind] = '\0';

	Mapa* m = newMapa(estados, alfabeto, iniciais, finais);	
	addNos(lista, m);
	episilon(m);
	if(processoFinal(m, argv[1]))
	{
		printf("O parâmetro passado está no estado de aceitação!\n");
	}
	else
	{
		printf("O parâmetro passado não está no estado de aceitação!\n");
	}
//	printMapa(m);

	return 0;
}
