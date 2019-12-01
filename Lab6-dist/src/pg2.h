#ifndef pg2Header
#define pg2Header

#include "LinkedList.h"

typedef struct _Arestas Arestas;

Arestas *           leFicheiroEDGE(char * nomeFicheiro, Arestas * aresta, int ** n_vertices);
Arestas * criaAresta(int inicio, int fim, int peso);
LinkedList ** criaLista(Arestas * aresta, int n_vertices);
void escreveFicheiro(char * nomeFicheiro, LinkedList ** lista, int n_vertices);

#endif