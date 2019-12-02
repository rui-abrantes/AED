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

Arestas * leFicheiroEDGE(char * nomeFicheiro, Arestas * aresta, int * n_arestas, int * n_vertices){

    FILE * file;
    int i;

    file = fopen(nomeFicheiro, "r");
    if(file == NULL){
        printf("\nCouldn't iniciate the file\n");
        exit(1);
    }

    if( fscanf(file, "%d", n_vertices )  != 1){
        printf("\nCouldn't read from the file\n");
        exit(1);
    }

    if( fscanf(file, "%d", n_arestas) != 1){
        printf("\nCouldn't read from the file\n");
        exit(1);
    }

    printf("\n\nNUMERO DE ARESTAS : %d \n\n", (*n_arestas));
    aresta = (Arestas *) malloc( (*n_arestas) * sizeof( Arestas  ) );
    if(aresta == NULL){
        printf("\nCouldn't allocate memory for the lista");
        exit(0);
    }

    for(i = 0; i< (*n_arestas); i++){
        fscanf(file, "%d %d %d", &aresta[i].inicio, &aresta[i].fim , &aresta[i].peso);

    }
    
    fclose(file);

    return aresta;
}


LinkedList ** criaLista(Arestas * aresta, int n_arestas, int n_vertices){

    int i,j;

    Arestas * aux = NULL;

    LinkedList ** lista;

    lista = (LinkedList **) calloc( n_vertices , sizeof(LinkedList * ));
    if( lista == NULL){
        printf("\nCouldn't allocate memory for the LinkedList");
        exit(1);
    }

    for ( i = 0; i < n_vertices ; i++){

        //printf("\nAresta[%d] -> %d : %d\n",i,aresta[i].inicio, aresta[i].fim);

        for(j = 0; j< n_arestas; j++){

            if( aresta[j].inicio == i){
                aux = criaAresta(i, aresta[j].fim, aresta[j].peso) ;
                //printf("\nAresta : [%d]  fim %d\n",i,aux->fim);
                lista[i] = insertUnsortedLinkedList(lista[i], (Item) aux);
            } else if (aresta[j].fim == i ){
                aux = criaAresta( i , aresta[j].inicio, aresta[j].peso);
                //printf("\nAresta2 : [%d]  inicio %d\n",i, aux->fim);
                lista[i] = insertUnsortedLinkedList(lista[i], (Item) aux);
            }
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
            lista_aux = getNextNodeLinkedList(lista_aux);

        }
        if( lista_aux == NULL){
            fprintf(file,"-1\n");
        }
    }
    fprintf(file,"-1\n");
    fclose(file);
}
