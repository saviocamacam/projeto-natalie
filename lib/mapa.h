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
		char val; //valor da entrada do programa
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


	typedef struct mapa
	{
		Node** vetor; 
		int n; //quantidade de estados
		char** labels; //nome dos estados
		int* type; //tipo do estado
		bool* state; //está ou nao no estado?
		lista_string* alf;
	}Mapa;

Mapa* newMapa(lista_string* estados, lista_string* alfabeto, lista_string* iniciais, lista_string* finais);
int addAresta(Mapa* l, int origem, int destino, char caracter);
bool removeAresta(Mapa* l, int origem, int destino);
bool isArestaVal(Mapa* l, int origem, int destino, char c);
bool isAresta(Mapa* l, int origem, int destino);
void printMapa(Mapa* l);	
int getMapa(Mapa* l, int*** endMapa);
Node* newNode(int valor);

#endif
