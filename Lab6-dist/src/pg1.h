#ifndef pg1Header
#define pg1Header

typedef struct _Grafo Grafo;
typedef struct _Aresta Aresta;

Grafo *             leFicheiro(char * nomeFicheiro);
void                libertaMatriz(Grafo * graph);
float               calculaDensidade(Grafo * graph);
int                 calculaGrauMax(Grafo * graph);
Aresta *            criaVetorAresta(Grafo * graph, Aresta * aresta);
void                ficheiroOut(char * nomeFile, Grafo * graph, Aresta * aresta);

#endif