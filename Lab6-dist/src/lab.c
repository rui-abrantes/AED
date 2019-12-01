#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "pg1.h"
#include "pg2.h"

int main(int argc, char *argv[]){

    Grafo * graph = NULL;
    LinkedList ** lista;
    Aresta * aresta = NULL;
    char * ficheirOut;
    int densidade, grau;
    int * n_vertices;
    int i;

    ficheirOut = (char *) malloc((strlen( argv[2] + 2) ) * sizeof(char));

    if(argc != 3){
        printf("\nYou forgot something, you should do : ./lab pg file.extention ");
        exit(0);
    }

    if( strcmp(argv[1], "pg1")){
        graph = leFicheiro(argv[2]);

        densidade = calculaDensidade(graph);
        printf("Densidade = %d\n", densidade);

        grau = calculaGrauMax(graph);
        printf("Grau = %d\n",grau);

        aresta = criaVetorAresta(graph, aresta);

        argv[2][stren(argv[2] - strlen("adj"))] = '\0';
        strcpy(ficheirOut,argv[2]);
        strcat(ficheirOut, "edge");


        ficheiroOut( ficheirOut,graph,aresta);
        libertaMatriz(graph);
        free(aresta);
    }
    else if (strcmp(argv[1], "pg2") ){
        aresta = leFicheiroEDGE(argv[2], aresta, n_vertices);
        lista = criaLista(aresta,(*n_vertices));

        argv[2][stren(argv[2] - strlen("edge"))] = '\0';
        strcpy(ficheiroOut,argv[2]);
        strcat(ficheiroOut, "ladj");

        escreveFicheiro(ficheirOut, lista, (*n_vertices));

        for( i= 0; i< (*n_vertices); i++)
            freeLinkedList(lista[i], free );

        free(lista);
        free(aresta);
    }
    else
        printf("\nYou choose the wrong pg, try again");

    free(ficheiroOut);

    return 0;
}