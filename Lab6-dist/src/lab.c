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
    Arestas * arestaPG2 = NULL;
    char * ficheirOut;
    int densidade, grau;
    int n_arestas = 0, n_vertices = 0;
    int i;

    ficheirOut = (char *) malloc((strlen( argv[2] ) + 2) * sizeof(char));

    if(argc != 3){
        printf("\nYou forgot something, you should do : ./lab pg file.extention ");
        exit(0);
    }

    if( strcmp(argv[1], "pg1") == 0){
        graph = leFicheiro(argv[2]);

        densidade = calculaDensidade(graph);
        printf("Densidade = %d\n", densidade);

        grau = calculaGrauMax(graph);
        printf("Grau = %d\n",grau);

        aresta = criaVetorAresta(graph);

        argv[2][strlen(argv[2]) - strlen("adj")] = '\0';
        strcpy(ficheirOut,argv[2]);
        strcat(ficheirOut, "edge");


        ficheiroOut( ficheirOut,graph,aresta);
        libertaMatriz(graph);
        free(graph);
        free(aresta);
    }
    else if (strcmp(argv[1], "pg2") == 0 ){
        arestaPG2 = leFicheiroEDGE(argv[2], arestaPG2, &n_arestas, &n_vertices);
        lista = criaLista(arestaPG2,n_arestas, n_vertices);

        argv[2][strlen(argv[2]) - strlen("edge")] = '\0';
        strcpy(ficheirOut, argv[2]);
        strcat(ficheirOut, "ladj");

        escreveFicheiro(ficheirOut, lista, n_vertices);

        for( i= 0; i< n_vertices; i++){
            freeLinkedList(lista[i], free );
        }

        free(lista);
        free(arestaPG2);
    }
    else
        printf("\nYou choose the wrong pg, try again");

    free(ficheirOut);

    return 0;
}