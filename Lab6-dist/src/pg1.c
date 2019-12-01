#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
typedef struct _Grafo{
    int n_vertices;
    int n_arestas;
    int ** matriz;

}Grafo;

typedef struct _Aresta {
    int inicio;
    int fim;
    int peso;
}Aresta;

Grafo * leFicheiro(char * nomeFicheiro, Grafo * graph){

    FILE * file;
    int i, j, peso;

    graph->n_arestas = 0;

    file = fopen(nomeFicheiro, "r");
    if(file == NULL){
        printf("\nCouldn't iniciate the file\n");
        exit(1);
    }

    if( fscanf(file, "%d", &graph->n_vertices) != 1){
        printf("\nCouldn't read from the file\n");
        exit(1);
    }

    graph->matriz = ( int**) malloc( graph->n_vertices * sizeof(int *));
    if( graph->matriz == NULL){
        printf("\nCouldn't allocate memory for the matrix");
        exit(1);
    }

    for( i = 0; i < graph->n_vertices; i++){
        graph->matriz[i] = ( int*) malloc( graph->n_vertices * sizeof(int ));
        if( graph->matriz[i] == NULL){
            printf("\nCouldn't allocate memory for the matrix");
            exit(1);
        }
    }

    for(i = 0; i< graph->n_vertices; i++){
        for(j = 0; j< graph->n_vertices; j++){
            if( fscanf(file, "%d", &peso) != 1){
                printf("\nCouldn't read from the file\n");
                exit(1);
            }
            graph->matriz[i][j] = peso;
            if( peso != 0 && i > j){
                graph->n_arestas ++;
            }
        }
    }
    fclose(file);
    return graph;
}

void libertaMatriz(Grafo * graph){
    int i;

    for(i = 0; i < graph->n_vertices; i++)
        free(graph->matriz[i]);
    free(graph->matriz);
}

float calculaDensidade(Grafo * graph){
    float densidade;

    densidade =(float) (2 * graph->n_arestas) / (float) graph->n_arestas;

    return densidade;
}

int calculaGrauMax(Grafo * graph){
    int i, j, grau, maxGrau = 0;

    for(i = 0; i< graph->n_vertices; i++){
        grau = 0;
        for(j = 0; j< graph->n_vertices; j++){  
            if(graph->matriz[i][j] != 0){
                grau ++;
            }
        }
        if( grau > maxGrau)
            maxGrau = grau ;
    }

    for(j = 0; j< graph->n_vertices; j++){
        grau = 0;
        for(i = 0; i< graph->n_vertices; i++){  
            if(graph->matriz[i][j] != 0){
                grau ++;
            }
        }
        if( grau > maxGrau)
            maxGrau = grau ;
    }



    return maxGrau;
}

Aresta * criaVetorAresta(Grafo * graph, Aresta * aresta){
    int i, j , posicaoAresta = 0, posicao;

    aresta = (Aresta * ) malloc( graph->n_arestas * sizeof(Aresta));
    if(aresta == NULL){
        printf("\nCouldn't allocate memory for the aresta");
        exit(0);
    }

    for(i = 0; i< graph->n_vertices; i++){
        for(j = 0; j< graph->n_vertices; j++){  
            if(graph->matriz[i][j] != 0 && i > j){
                aresta[posicaoAresta].inicio = i;
                aresta[posicaoAresta].fim = j;
                aresta[posicaoAresta].peso = graph->matriz[i][j];
                posicaoAresta ++;
                         
            }
        }
    }
}

void ficheiroOut(char * nomeFile, Grafo * graph, Aresta * aresta){

    FILE * file;
    int i;

    file = fopen(nomeFile, "w");

    fprintf(file, "%d\n%d\n", graph->n_vertices, graph->n_arestas);

    for( i = 0; i < graph->n_arestas; i++){
        fprintf(file,"%d %d %d", aresta[i].inicio, aresta[i].fim, aresta[i].peso);
    }

}

