#ifndef __MAPAAUTOMATOS__
#define __MAPAAUTOMATOS__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum boolean
	{
		false = 0,true = 1
	}bool;

	typedef struct node
	{
		char val; //caractere de transição
		char escreve; //o que escreve depois
		char orientacao; //para onde ir depois?
		int data;
		struct node * next;
	}Node;


//	typedef struct
//	{
//		char* alfabeto;
//		int alfabetotam;
//	}Alfabeto;

	typedef struct {
		char ** string;
		int qtd;
	}lista_string;

	typedef struct NodeFita{
		char valor; //valor daquela posição da fita
		struct NodeFita *next;
		struct NodeFita *prev;
	}nofita;
	
	typedef struct fita{
		struct fita* next;
		nofita* posicao;
		bool valido; //verifica se a fita é valida ou não
		int ind; //indica o indice que represenra seus states no mapa
		int size; 
		int sizeInicial;
		lista_string* alfabeto;
		lista_string* nulo; //aqui coloquei como 2 para que possa ser comparado como string, assim podemos ter uma unica palavra que represente o caractere nulo;
	}Fita;	

	typedef struct {
		Fita* atual; 
		int size;
		int validos; //validos e valido da fita
	}gerenciadorFita;

	typedef struct mapa
	{
		Node** vetor; 
		int n; //quantidade de estados
		char** labels; //nome dos estados
		int* type; //tipo do estado
		bool** state; //está ou nao no estado? //mudar com matriz **
		lista_string* alf;
	}Mapa;

void cloneGeral(Mapa *m, gerenciadorFita *g, bool *newstate, Fita *clonar);

gerenciadorFita* newGerenciador();
void addFita(gerenciadorFita* g, Fita *f);
Fita* clonaFita(Fita* f);
void imprimeFita(Fita* f);
Fita* newFita(char* entradas, lista_string* alfabeto, lista_string* nulo);
bool escritaFita(Fita* f, char escreve, char orientacao); //orientação, move para a direita, para a esquerda ou mantem (R,L,S), se movimentar na direcão do vazio, então gera mais um nó com a posição vazio
char leituraFita(Fita* f); //le a posição da fita

Mapa* newMapa(lista_string* estados, lista_string* alfabeto, lista_string* iniciais, lista_string* finais);
int addAresta(Mapa* l, int origem, int destino, char caracter, char escreve, char orientacao);
bool removeAresta(Mapa* l, int origem, int destino);
bool isArestaVal(Mapa* l, int origem, int destino, char c, char* ESC, char* ORI);
bool isAresta(Mapa* l, int origem, int destino);
void printMapa(Mapa* l);	
int getMapa(Mapa* l, int*** endMapa);
Node* newNode(int valor);

#endif
