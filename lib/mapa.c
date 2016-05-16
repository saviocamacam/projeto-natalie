#include "mapa.h"

Mapa* newMapa(lista_string* estados, lista_string* alfabeto, lista_string* iniciais, lista_string* finais)
{
		int i, n;
		n = estados->qtd;
		Node **pno; //ponteiro de ponteiro de nó
		Mapa* l;
		l = (Mapa*) malloc(sizeof(Mapa));
		while(n < 0)
		{
				printf("Quantidade de estados inválido!!!");
				exit(0);
//				scanf("%d", &n);
		}
		l->n = n; 
		pno = (Node**) malloc(sizeof(Node*)*n);

		l->vetor = pno;
		l->state = (bool*) malloc(sizeof(bool)*n);
		l->alf = alfabeto;
		l->labels = estados->string;
		l->type = (int*) malloc(sizeof(int)*n);
		/*inicializando o vetor;*/
		for (i=0; i<n; i++)
		{
				l->vetor[i] = NULL;	
				l->state[i] = false;
				l->type[i] = 0;
		}

		//declarando os estados
		int j;
		for (j=0; j<iniciais->qtd; j++)
		{
			for(i=0; i<n; i++)
			{
				if (strcmp(l->labels[i],iniciais->string[j])==0)
				{
					l->type[i] = -1;
					l->state[i] = true;  
				}
			}
		}
		
		for (j=0; j<finais->qtd; j++)
		{
			for(i=0; i<n; i++)
			{
				if (strcmp(l->labels[i],finais->string[j])==0)
				{
					l->type[i] = 1;
				}
			}
		}

	
		return(l);
}

int addAresta(Mapa* l, int origem, int destino, char caracter, char escreve, char orientacao)
{
		/*verifica se os valores passados como parametros são válidos*/
/*		if ((origem > l->n) || (origem < 0) || (destino > l->n) || (destino < 0))
		{
				return(false);
		}
		
		*verifica se já existe a conexão, se já ele retorna -1*
		if (isAresta(l, origem, destino))
		{
				return(-1);
		}*/
		
		/*faz a conexão da origem com destino*/
		Node* aux;
		aux = (Node*) malloc(sizeof(Node));
		aux->data = destino;
		aux->val = caracter;
		aux->escreve = escreve;
		aux->orientacao = orientacao;
		aux->next = l->vetor[origem];		
		l->vetor[origem] = aux;

/*		*faz a conexão do destino com a origem*
		Node* aux2;
		aux2 = (Node*) malloc(sizeof(Node));
		aux2->data = origem;
		aux2->next = l->vetor[destino];
		l->vetor[destino] = aux2; */
		return(true);
}

bool removeAresta(Mapa* l, int origem, int destino)
{
		/*verifica se os valores digitados são válidos*/
		if ((origem >= l->n) || (origem < 0) || (destino >= l->n) || (destino < 0))
		{
				return(false);
		}
		
		/*verifica se há conexão origem - destino e destino origem*/
		if (/*(isAresta(l, origem, destino)) &&*/ (isAresta(l, destino, origem)))
		{
				
				Node *redutor=NULL, *redutorprev=NULL;  
				redutor = l->vetor[origem];

				/*redutor aponta para o nó que deve ser removido */
				/*redutorprev aponta para o enelemento anterior*/
				while (redutor->data != destino)
				{
					redutorprev = redutor;
					redutor = redutor->next;
				}
				
				/*verifica se o nó escolhido é o primeiro do vetor*/
				if (redutorprev != NULL)
				{
						redutorprev->next = redutor->next;
						redutor->next = NULL;
						free(redutor);
				}
				else
				{
						l->vetor[origem] = redutor->next;
						redutor->next = NULL;
						free(redutor);
				}

				/*removida a conexão origem destino*/


				redutorprev = NULL;
				redutor = l->vetor[destino]; 

				/*redutor aponta para o nó que deve ser removido */
				/*redutorprev aponta para o enelemento anterior*/
				while (redutor->data != origem)
				{
					redutorprev = redutor;
					redutor = redutor->next;
				}
				
				/*verifica se o nó escolhido é o primeiro do vetor*/
				if (redutorprev != NULL)
				{
						redutorprev->next = redutor->next;
						redutor->next = NULL;
						free(redutor);
				}
				else
				{
						l->vetor[destino] = redutor->next;
						redutor->next = NULL;
						free(redutor);
				}
				

				/*removida a conexão destino - origem*/

		return(true); //um passo para o sucesso!
		}
		else
		{
		return(false); // se não tinha comunicação retorna falso
		}	

}

bool isArestaVal(Mapa* l, int origem, int destino, char c, char* ESC, char* ORI)
{

		Node* redutor;

		redutor = l->vetor[origem];
		while (redutor != NULL)
		{
				if ((redutor->data == destino) && (redutor->val == c))
				{
					ESC[0] = redutor->escreve;
					ORI[0] = redutor->orientacao;
						return(true);
				}
				redutor = redutor->next;
		}		
		return(false);
}

bool isAresta(Mapa* l, int origem, int destino)
{

		Node* redutor;

		redutor = l->vetor[origem];
		while (redutor != NULL)
		{
				if (redutor->data == destino)
				{
						return(true);
				}
				redutor = redutor->next;
		}		
		return(false);
}
void printMapa(Mapa* l) 
{
		int i;
		Node* redutor;

//	printf("valor de i = %d\n", l->n);	
		for (i=0; i<l->n; i++)
		{
				redutor = l->vetor[i];
				printf("Nó %s: \n",l->labels[i]);
						while (redutor != NULL)
						{
		//						printf("%d - %c\n", redutor->data, redutor->val);
								printf("%s - %c - %c - %c\n", l->labels[redutor->data], redutor->val, redutor->escreve, redutor->orientacao);
								redutor = redutor->next;
						}
		}
}

int getMatriz(Mapa* l, int*** endMatriz)
{
		int i, j;
		int **mat;

		/*cria o vetor de ponteiros*/
		mat = (int**) malloc(sizeof(int*)*l->n);


		/*cria as posições verticais*/
		for (i=0; i<(l->n); i++)
		{
			mat[i] = (int*) malloc(sizeof(int)*l->n);
		}

	 /*preenche a matriz*/
		for (i=0; i<(l->n); i++)  
		{
				for (j=0; j<(l->n); j++)
				{
						if (isAresta(l, i, j))
						{
								mat[i][j] = 1;
						}
						else
						{
								mat[i][j] = 0;
						}
				}
		}
 
		*endMatriz = mat;
		return(1);
}

//void mudaEstado(Mapa* m, char c)

	


Node* newNode(int data)
{
	Node* new;
  	new = (Node*) malloc(sizeof(int));
	new->data = data;
	new->next = NULL;
	return(new);
}

Fita* newFita(char* entradas, lista_string* alfabeto, lista_string* nulo)
{
	Fita* aux = (Fita*) malloc(sizeof(Fita));
	aux->alfabeto = alfabeto;
	aux->nulo = nulo;
	aux->posicao = NULL;
	aux->size = 0;
	int i, size;
	size = strlen(entradas);
	for (i=size-1; i>=0; i--)
	{
		nofita *noaux = (nofita*) malloc(sizeof(nofita));
		noaux->next = aux->posicao;
		noaux->prev = NULL;
		noaux->valor = entradas[i];
		aux->posicao = noaux;
		aux->size++;
	} 
aux->sizeInicial = aux->size;
return(aux);
}

bool escritaFita(Fita* f, char escreve, char orientacao)
{
	int i;
	bool verif = true;
	for(i=0; i<f->alfabeto->qtd; i++)
	{
		
		if((f->alfabeto->string[i][0] == escreve) && ((orientacao == 'R') || (orientacao == 'L') || (orientacao == 'S')))
		{
			verif = false;
			break;
		}
	}
	
	if(verif)
	{
		printf("Erro na escrita, a escrita não está no alfabeto da fita ou a orientação nao existe!\n");
//		exit(0);
	}

	
	if (f->posicao == NULL)
	{
				nofita *noaux = (nofita*) malloc(sizeof(nofita));
				noaux->next = NULL;
				noaux->prev = NULL;
				noaux->valor = f->nulo->string[0][0];
				f->posicao = noaux;
				f->size++;
		return(false);
	}
	else
	{
		f->posicao->valor = escreve;
		if(orientacao == 'R')
		{
			if(f->posicao->next == NULL)
			{
				nofita *noaux = (nofita*) malloc(sizeof(nofita));
				noaux->next = f->posicao->next; //NULL
				noaux->prev = f->posicao;
				noaux->valor = f->nulo->string[0][0];
				f->posicao->next = noaux;
				f->size++;
			}
			f->posicao = f->posicao->next;
		}
		else
		{
			if (orientacao == 'L')
			{
				if (f->posicao->prev == NULL)
				{
					nofita *noaux = (nofita*) malloc(sizeof(nofita));
					noaux->next = f->posicao; 
					noaux->prev = f->posicao->prev; //NULL
					noaux->valor = f->nulo->string[0][0];
					f->posicao->prev = noaux;
					f->size++;
				}
				f->posicao = f->posicao->prev;
			}
			//else stay, mas como não é necessario fazer nada, nada o façamos
		}	
	}
return(true);
}

char leituraFita(Fita* f)
{
	if (f->posicao == NULL)
	{
		return(f->nulo->string[0][0]);
	}
	else
	{
		return(f->posicao->valor);
	}
}

gerenciadorFita* newGerenciador()
{
	gerenciadorFita* g = (gerenciadorFita*) malloc(sizeof(gerenciadorFita));
	g->atual = NULL;
	g->size = 0;
	return(g);
}

void addFita(gerenciadorFita* g, Fita *f)//fila circular
{
	if (g->atual == NULL)
	{
		g->atual = f;
		f->next = f;
	}
	else
	{
		f->next = g->atual->next;
		g->atual->next = f;
	}
	g->size++;
}

Fita* clonaFita(Fita* f)
{
	fita
}
