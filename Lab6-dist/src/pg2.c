#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "pg2.h"
#include "LinkedList.h"

typedef struct _Arestas {
    int inicio;
    int fim;
    int peso;
}Arestas;

Arestas * criaAresta(int inicio, int fim, int peso){
    Arestas * new;
    new = (Arestas *) malloc( sizeof(Arestas));
    if(new == NULL){
        printf("\nCouldnt allocate memory for the Arestas\n");
        exit(1);
    }
    new->fim = fim;
    new->inicio = inicio;
    new->peso = peso;

    return new;
}

Arestas * leFicheiroEDGE(char * nomeFicheiro, Arestas * aresta, int * n_vertices){

    FILE * file;
    int i, j, peso, vertices, arestas;

    file = fopen(nomeFicheiro, "r");
    if(file == NULL){
        printf("\nCouldn't iniciate the file\n");
        exit(1);
    }

    if( fscanf(file, "%d", n_vertices )  != 1){
        printf("\nCouldn't read from the file\n");
        exit(1);
    }

    if( fscanf(file, "%d", arestas) != 1){
        printf("\nCouldn't read from the file\n");
        exit(1);
    }

    aresta = (Arestas *) malloc( arestas * sizeof( Arestas  ) );
    if(aresta == NULL){
        printf("\nCouldn't allocate memory for the lista");
        exit(0);
    }

    for(i = 0; i< arestas; i++){
        fscanf(file, "%d %d %d", &aresta[i].inicio, &aresta[i].fim , &aresta[i].peso);
    }
    fclose(file);

    return aresta;
}


LinkedList ** criaLista(Arestas * aresta, int n_vertices){

    int i;

    Arestas * aux = NULL;

    LinkedList ** lista;

    lista = (LinkedList **) malloc( n_vertices * sizeof(LinkedList * ));
    if( lista == NULL){
        printf("\nCouldn't allocate memory for the LinkedList");
        exit(1);
    }

    for ( i = 0; i < n_vertices ; i++){
        if( aresta->inicio == i){
            aux = criaAresta(i, aresta->fim, aresta->peso) ;
            lista[i] = insertUnsortedLinkedList(lista[i], (Item) aux);
        }
        else if (aresta->fim == i ){
            aux = criaAresta( aresta->inicio , i, aresta->peso);
            lista[i] = insertUnsortedLinkedList(lista[i], (Item) aux);
        }
    }

    return lista;
}

void escreveFicheiro(char * nomeFicheiro, LinkedList ** lista, int n_vertices){
    FILE * file;
    
    Arestas * aux;

    LinkedList * lista_aux;

    int i;

    file = fopen(nomeFicheiro, "w" );

    for(i = 0; i< n_vertices; i++){
        lista_aux = lista[i];
        while(lista_aux != NULL){
            aux = getItemLinkedList(lista_aux);
            fprintf(file,"%d:%d ", aux->fim, aux->peso);

        }
        if( lista[i] == NULL){
            fprintf(file," -1\n");
        }
    }
    fclose(file);
}
