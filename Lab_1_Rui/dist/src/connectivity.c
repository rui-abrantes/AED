/******************************************************************************
* (c) 2010-2019 AED Team
* Last modified: abl 2019-02-22
*
* NAME
*   connectivity.c
*
* DESCRIPTION
*   Algorithms for solving the connectivity problem -  QF QU WQU CWQU
*   For each method count number of entry pairs and the number of links
*
* COMMENTS
*   Code for public distribution
******************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "connectivity.h"


/******************************************************************************
* quick_find()
*
* Arguments: id - array with connectivity information
*            N - size of array
*            fp - file pointer to read data from
*            quietOut - to reduce output to just final count
* Returns: (void)
* Side-Effects: pairs of elements are read and the connectivity array is
*               modified
*
* Description: Quick Find algorithm
*****************************************************************************/
void quick_find(int *id, int N, FILE * fp, int quietOut)
{
    int i, p, q, t;
    int pairs_cnt = 0;            /* connection pairs counter */
    int links_cnt = 0;            /* number of links counter */
    long int find = 0;             // number of times that the program read 
                                        // (done by the student)
    long int union_cnt = 0;            // number of times that the probram wrote 
                                        //(done by the student)
    long int elemental_op = 0;         // number of elemental operations
                                        //(done by the student)

    /* initialize; all disconnected */
    for (i = 0; i < N; i++) {
        elemental_op++;
        id[i] = i;
    }

    /* read while there is data */
    while (fscanf(fp, "%d %d", &p, &q) == 2) {
        pairs_cnt++;
        /* do search first */
        find+=2;; // sempre que compara tem que ler 2 valores
        if (id[p] == id[q]) {
                         // logo acaba por ler 2 vezes
            /* already in the same set; discard */
            if (!quietOut)
                printf("\t%d %d\n", p, q);
            continue;
        }

        /* pair has new info; must perform union */
        
        for (t = id[p], i = 0; i < N; i++) {
            union_cnt++; // para comparar se o id[i] == t tem que ler 1 valor
            if (id[i] == t) {

                id[i] = id[q];
                union_cnt+=2; // aqui escreve 1 valor lido dum outro
            }
        }
        union_cnt++;
        links_cnt++;
        if (!quietOut)
            printf(" %d %d\n", p, q);
    }

    elemental_op = find + union_cnt + elemental_op;
    printf("QF: The number of links performed is %d for %d input pairs.\n",
            links_cnt, pairs_cnt);
    printf("QF: The number of find's performed is %ld\n", find);
    printf("QF: The number of union's performed is %ld\n", union_cnt);
    printf("QF: The number of elemental operation is performed is %ld\n\n", elemental_op);
    return;
}


/******************************************************************************
* quick_union()
*
* Arguments: id - array with connectivity information
*            N - size of array
*            fp - file pointer to read data from
*            quietOut - to reduce output to just final count
* Returns: (void)
* Side-Effects: pairs of elements are read and the connectivity array is
*               modified
*
* Description: Quick Union algorithm
*****************************************************************************/
void quick_union(int *id, int N, FILE * fp, int quietOut)
{

    int i, j, p, q, j2;
    int pairs_cnt = 0;            /* connection pairs counter */
    int links_cnt = 0;            /* number of links counter */

    int conjuntos_cnt = 1;        /* indicates the number of sets */
    int *heads = (int * ) malloc( sizeof(int)) ; // é possivel por aqui malloc de N
                                                 //e nao usar realloc

    long int find = 0;             // number of times that the program read 
                                        // (done by the student)
    long int union_cnt = 0;            // number of times that the probram wrote 
                                        //(done by the student)
    long int elemental_op = 0;         // number of elemental operations
                                        //(done by the student)
    
    heads[0] = N ;
    int counter = 1; /* it's and auxiliar to helps us count the conjuntos_cnt */

    /* initialize; all disconnected */
    for (i = 0; i < N; i++) {
        id[i] = i;
        elemental_op = elemental_op + 1;
    }

    /* read while there is data */
    while (fscanf(fp, "%d %d", &p, &q) == 2) {
        pairs_cnt++;
        i = p;
        j = q;

        /* do search first / encontrar a cabeça */
        find+=2; /*sempre que recebe 1 par irá lê-lo nos while's*/
        while (i != id[i]) {
            i = id[i];
            find+=2; /*sempre que entra no loop e obrigado a ler outro dado*/
        }
        while (j != id[j]) {
            j = id[j];
            find+=2;
        }
        if (i == j) {
            /* already in the same set; discard */
            if (!quietOut)
                printf("\t%d %d\n", p, q);
            continue;
        }

        /* pair has new info; must perform union */
        id[i] = j;
        union_cnt++;

        links_cnt++;

        if (!quietOut)
            printf(" %d %d\n", p, q);
    }

    /**************************FIM DO ALGORITOMO*******************************/
    /* quando o algoritmo acabou é que devo de ir ver os conjuntos "criados" */

    j = 0;
    while (j != id[j]) {
            j = id[j];
    }
    heads[0] = j;

    /* obriga a passar por todos os elementos, para se ter a certeza de que 
    se vê todos os conjuntos possiveis */

    for(i = 0; i<N;i++){
        j = i;
        while (j != id[j]) {
            j = id[j];
        }

        /* check if the head of the set has already been seen */
        for(j2 = 0; j2 < conjuntos_cnt; j2++){
            if(j != heads[j2]){
                counter++;
            }
        }
        if(counter != conjuntos_cnt){
            conjuntos_cnt++;

            //nao e necessario usar isto caso se use o malloc de N em cima
            heads = (int *) realloc (heads,conjuntos_cnt * sizeof(int));
            heads[conjuntos_cnt - 1] = j;
        }
    }

    elemental_op = find + union_cnt + elemental_op;
    printf("\nQU: The number of links performed is %d for %d input pairs.\n",
            links_cnt, pairs_cnt);
    printf("QU: The number of find's performed is %ld\n", find);
    printf("QU: The number of union's performed is %ld\n", union_cnt);
    printf("QU: The number of elemental operation is performed is %ld\n\n", elemental_op);

    /* vai pegar na cabeca de cada conjunto e andar para tras enquanto escreve no stdout */

    /*
    for(i = 0; i < conjuntos_cnt; i++){
        printf("%d",heads[i]);
        while (1)
        {   
            for(j = 0; j<N; j++){
                j2 = j;

                while (j2 != id[j2]) {
                    j2 = id[j2];
                }

                if(j2 == heads[i] && j2!=j ){
                    printf("-%d",j);
                } 
            }
            break;
        }
        printf("\n");
    }
    printf("O numero de conjuntos é: %d\n", conjuntos_cnt);
    */
}


/******************************************************************************
* weighted_quick_union()
*
* Arguments: id - array with connectivity information
*            N - size of array
*            fp - file pointer to read data from
*            quietOut - to reduce output to just final count
* Returns: (void)
* Side-Effects: pairs of elements are read and the connectivity array is
*               modified
*
* Description: Weighted Quick Union algorithm
*****************************************************************************/
void weighted_quick_union(int *id, int N, FILE * fp, int quietOut)
{

    int i, j, p, q;
    int *sz = (int *) malloc(N * sizeof(int));
    int pairs_cnt = 0;            /* connection pairs counter */
    int links_cnt = 0;            /* number of links counter */

    long int find = 0;             // number of times that the program read 
                                        // (done by the student)
    long int union_cnt = 0;            // number of times that the probram wrote 
                                        //(done by the student)
    long int elemental_op = 0;         // number of elemental operations
                                        //(done by the student)

    /* initialize; all disconnected */
    for (i = 0; i < N; i++) {
        elemental_op+=2;
        id[i] = i;
        sz[i] = 1;
    }

    /* read while there is data */
    while (fscanf(fp, "%d %d", &p, &q) == 2) {
        pairs_cnt++;

        find+=2;
        /* do search first */
        for (i = p; i != id[i]; i = id[i]) {
            find+=2;
        }
        for (j = q; j != id[j]; j = id[j]) {
            find+=2 ;
        }

        if (i == j) {
            /* already in the same set; discard */
            if (!quietOut)
                printf("\t%d %d\n", p, q);
            continue;
        }

        /* pair has new info; must perform union; pick right direction */
        union_cnt+=2;
        if (sz[i] < sz[j]) {
            union_cnt+=3;
            id[i] = j;
            sz[j] += sz[i];
        }
        else {
            union_cnt+=3;
            id[j] = i;
            sz[i] += sz[j];
        }
        links_cnt++;

        if (!quietOut)
            printf(" %d %d\n", p, q);
    }

    elemental_op = union_cnt + find + elemental_op;
    printf("WQU: The number of links performed is %d for %d input pairs.\n",
            links_cnt, pairs_cnt);
    printf("QF: The number of find's performed is %ld\n", find);
    printf("QF: The number of union's performed is %ld\n", union_cnt);
    printf("QF: The number of elemental operation is performed is %ld\n\n", elemental_op);
}


/******************************************************************************
* compressed_weighted_quick_union()
*
* Arguments: id - array with connectivity information
*            N - size of array
*            fp - file pointer to read data from
*            quietOut - to reduce output to just final count
* Returns: (void)
* Side-Effects: pairs of elements are read and the connectivity array is
*               modified
*
* Description: Compressed Weighted Quick Union algorithm
*****************************************************************************/
void compressed_weighted_quick_union(int *id, int N, FILE * fp, int quietOut)
{
    int i, j, p, q, t, x;
    int *sz = (int *) malloc(N * sizeof(int));
    int pairs_cnt = 0;            /* connection pairs counter */
    int links_cnt = 0;            /* number of links counter */

    long int find = 0;             // number of times that the program read 
                                        // (done by the student)
    long int union_cnt = 0;            // number of times that the probram wrote 
                                        //(done by the student)
    long int elemental_op = 0;         // number of elemental operations
                                        //(done by the student)

    /* initialize; all disconnected */
    for (i = 0; i < N; i++) {
        elemental_op +=2;
        id[i] = i;
        sz[i] = 1;
    }

    /* read while there is data */
    while (fscanf(fp, "%d %d", &p, &q) == 2) {
        pairs_cnt++;

        /* do search first */
        find +=2;
        for (i = p; i != id[i]; i = id[i]) find += 2;
        for (j = q; j != id[j]; j = id[j]) find += 2;

        if (i == j) {
            /* already in the same set; discard */
            if (!quietOut)
                printf("\t%d %d\n", p, q);
            continue;
        }

        /* pair has new info; must perform union; pick right direction */
        union_cnt +=2;
        if (sz[i] < sz[j]) {
            union_cnt +=3;
            id[i] = j;
            sz[j] += sz[i];
            t = j;
        }
        else {
            union_cnt +=3;
            id[j] = i;
            sz[i] += sz[j];
            t = i;
        }
        links_cnt++;

        /* retrace the path and compress to the top */
        union_cnt +=2;
        for (i = p; i != id[i]; i = x) {
            union_cnt +=2;
            x = id[i];
            id[i] = t;
        }
        for (j = q; j != id[j]; j = x) {
            union_cnt +=2;
            x = id[j];
            id[j] = t;
        }
        if (!quietOut)
            printf(" %d %d\n", p, q);
    }

    elemental_op = find + union_cnt + elemental_op;
    printf("CWQU: The number of links performed is %d for %d input pairs.\n",
            links_cnt, pairs_cnt);
    printf("CWQF: The number of find's performed is %ld\n", find);
    printf("CWQF: The number of union's performed is %ld\n", union_cnt);
    printf("CWQF: The number of elemental operation is performed is %ld\n\n", elemental_op);

    return;
}
