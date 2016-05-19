#include "../lib/mapa.h"
#define T 100

bool verficador(Mapa* m, gerenciadorFita* g)
{
	int i;
	int indice = g->atual->ind;

	for (i=0; i<m->n; i++)
	{
		if(m->state[indice][i] == true)
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

	for (i=6; i<l->qtd-1; i++)// 6 pois pula as linhas que não tem acesso TODO se faltar alguma linha ver aqui
	{
		aux = listaEstados(l,i);
		bool verif = true;
		for (j=0; j<m->alf->qtd; j++) //de 0 ate a quantidade de caracteres no alfabeto
		{
			//	printf("%s, %s, %d, %d\n", aux->string[1], m->alf->string[j], strcmp(aux->string[1], m->alf->string[j]), m->alf->qtd);i
		//	printf("string[%d]: %s\n",i, aux->string[1]);
			if (!strcmp(aux->string[1], m->alf->string[j])) //se encontrar no alfabeto muda para false e nao entra no prox if
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
		for (k=0; k<m->n; k++) //de 0 ate a quantidade de estados
		{
			if (!strcmp(aux->string[0],m->labels[k])) //se o primeiro estado é igual ao label k
			{
				for (z=0; z<m->n; z++) //de 0 ate a quantidade de estados
				{	
					if (!strcmp(aux->string[2],m->labels[z])) //se o segundo é igual ao label z
					{	
						//				printf("foi adicionado, or:%d des:%d va:%s %d\n", k,z,aux->string[1], m->n);

						addAresta(m,k,z,aux->string[1][0], aux->string[3][0], aux->string[4][0]); //add mapa, primeiro, segundo, caractere da transição,  string 3 = escrita....string 4 = orientação
						//printMapa(m);
					}
				}
			}

		}


	}
}

////////////////////////////
/*void episilon(Mapa* m)
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
  }*/



bool processoFinal(Mapa* m, gerenciadorFita* g)
{	

	if (g->validos == 0) //se não existir nenhuma fita valida entao a maquina parou e não está em estado de aceitação
	{
		return(false);
	}



	int i, j, k, z, count=0, indice;
	bool modf[m->n];
	char esc[255]; 
	char ori[255];

	Fita* f = g->atual;

	indice = f->ind;


	while((f->size - f->sizeInicial) >= 100)
	{
		char verif;	
		printf("Há mais de %d elementos na fita, deseja continuar a execução? s/n\n", f->size);
		setbuf(stdin,NULL);
		setbuf(stdout,NULL);
		verif = getchar();
		getchar(); //tira o /n com uma gambiarra
		setbuf(stdin,NULL);
		setbuf(stdout,NULL);
		if (verif == 's')
		{
			f->sizeInicial = f->size;
		}
		else
		{
			if (verif == 'n')
			{
				exit(0);
			}
		}
	}

	if (!g->atual->valido) //se a fita está inválidada
	{
		g->atual = g->atual->next;
		return(processoFinal(m, g));
	}

	for (i=0; i<m->n; i++)
	{
		modf[i] = false;	
	}


	for(j=0; j<m->n; j++)
	{
		if (m->state[indice][j])
		{
			for(k=0; k<m->n; k++)
			{
				if (isArestaVal(m,j,k,leituraFita(f), &esc[count], &ori[count])) //tentar usar direto ao inves da função leitura 
				{
					modf[k] = true;
					count++; //se esse count > 1 então há não determinismo
				}

			}
		}
	}
	
	count = 0; //zera o count para fazer as novas escritas
	bool primeiravez = true; //é o primeiro true do vetor?
	for (z=0; z<m->n; z++) //estado atual
	{

		if (modf[z]) //se for true
		{
			if (primeiravez) //e primeira vez,então pode ser que não há não determinismo	
			{
				primeiravez = false;
				count++;
			}
			else //se entrar aqui é pq há um não determinismo
			{
				bool *newstate = (bool*) malloc(sizeof(bool)*m->n); //cria todos os estados para o novo clone
				int a;
				for (a=0; a<m->n; a++)
				{
					if (a == z) //apenas a posição z fica em true
					{
						newstate[a] = true;
					}
					else //as outras posições ficam false
					{
						newstate[a] = false;
					}
				}
				Fita* novafita = clonaFita(f);
				escritaFita(novafita,esc[count], ori[count]);	
				cloneGeral(m, g, newstate, novafita);
				modf[z] = false; //esse modf se torna falso para retirar o determinismo desta fita
				count++;	
			}
		}
		m->state[indice][z] = modf[z];
	}


	bool existrue = false; //existe algum estado em true?
//imprimeFita(f);
	for (i=0; i<m->n; i++)//verifica se está em estado de aceitação
	{		
		if(m->state[indice][i])
		{//printf("Está aqui %d\n", i);

			existrue  = true;

			if (m->type[i] == 1)
			{	
				return(true);
			}
		}
	}

	g->atual = g->atual->next;
	if (existrue)
	{

		escritaFita(f, esc[0], ori[0]);
		return(processoFinal(m,g));
	}
	else
	{
		f->valido = false; //invalida a fita!!
//imprimeFita(f);
		g->validos--;
		return(processoFinal(m,g));	
	}
}

int main(int argc, char* argv[]) {
	if (argc <= 1)
	{
		printf("Digite uma palavra no parâmetro!!\n");
		return(0);
	}


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
	//	lista_string* alfabeto = listaEstados(lista, 0);//automato
	//	lista_string* estados = listaEstados(lista, 1);
	//	lista_string* iniciais = listaEstados(lista, 2);
	//	lista_string* finais = listaEstados(lista,3);


	lista_string* alfabeto = listaEstados(lista, 0);//automato
	lista_string* alfabetoFita = listaEstados(lista, 1);
	lista_string* estados = listaEstados(lista, 2);
	lista_string* blank = listaEstados(lista,3);
	lista_string* iniciais = listaEstados(lista,4);
	lista_string* finais = listaEstados(lista,5);


	//alfabeto->string[1][1] = '\0';
	//while(p != 13)
	{
		//	ind++;
		//	p = alfabeto->string[1][ind];
	}
	//alfabeto->string[1][ind] = '\0';

	Mapa* m = newMapa(estados, alfabeto, iniciais, finais);	
	addNos(lista, m);
	gerenciadorFita* g = newGerenciador();
	addFita(g,newFita(argv[1], alfabetoFita, blank));
	//	episilon(m);
	if(processoFinal(m, g))
	{
		printf("O parâmetro passado está no estado de aceitação!\n");
	}
	else
	{
		printf("O parâmetro passado não está no estado de aceitação!\n");
	}
	printMapa(m);

	return 0;
}
