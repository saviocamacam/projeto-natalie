#include "../lib/mapa.h"
	
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

int main()
{	
	Mapa m;
//	m = newMapa();	 //passar como parametro a quantidade de estados
	
	
			
	return(0);
}
