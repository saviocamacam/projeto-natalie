#ifndef __MAPAAUTOMATOS__
#define __MAPAAUTOMATOS__
#include <stdio.h>
#include <stdlib.h>

typedef enum boolean
	{
		false = 0,true = 1
	}bool;

	typedef struct node
	{
		char data; //valor da entrada do programa
		struct node * next;
	}Node;


	typedef struct
	{
		char* alfabeto;
		int alfabetotam;
	}Alfabeto;

	typedef struct mapa
	{
		Node** vetor; 
		int n; //quantidade de estados
		char** labels; //nome dos estados
		int* type; //tipo do estado
		bool* state; //está ou nao no estado?
<<<<<<< HEAD
		Alfabeto* alf;
=======
		
>>>>>>> 091a0ee777219b9b734bd67299e787eb7f4eb332
	}Mapa;

Mapa* newMapa(int n);
int addAresta(Mapa* l, int origem, int destino);
bool removeAresta(Mapa* l, int origem, int destino);
bool isAresta(Mapa* l, int origem, int destino);
void printMapa(Mapa* l);	
int getMapa(Mapa* l, int*** endMapa);
Node* newNode(int valor);

#endif
