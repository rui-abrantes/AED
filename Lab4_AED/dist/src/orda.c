/******************************************************************************
* (c) 2010-2019 AED Team
* Last modified: abl 2019-04-02
*
* NAME
*   orda.c
*
* DESCRIPTION
*   Main program for unique word finding and sorting with tables
*
* COMMENTS
*   Code for preliminary distribution, to be completed
******************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#include "word.h"

enum sort_order {ascending, descending};

enum sort_criteria {alphabetic, length, occurrences};


int OP_CNT = 0;     /* global variable, to simplify complexity assessment */


/******************************************************************************
* sort ()
*
* Arguments: a - table of items to sort
*            l, r - limits on table to consider
*            less - item comparison function
* Returns: (void)
* Side-Effects: table is sorted in place
*
* Description: implements "some" abstract type (Item) sorting algorithm,
*		using also an abstract type comparison function (*less)
*		   a[] - array of abstract type Item to be sorted
*		   l - index of first element in the array to be sorted
*		   r  -last element of the array to be sorted
*		   (*less)(Item,Item) - abstract type comparison function
*****************************************************************************/


/* SORT DO PROFESSOR É INSERTION SORT!!!*/
void sort(Item a[], int l, int r, int (*less) (Item, Item))
{
    int i, j;

    for (i = l + 1; i <= r; i++) {
        Item v = a[i];
        j = i;
        OP_CNT++;
        while (j > l && less(v, a[j - 1]) ) {
            a[j] = a[j - 1];
            OP_CNT++;
            j--;
        }
        OP_CNT++;
        a[j] = v;
    }
    return;
}


/******************************************************************************
* main ()
*
*****************************************************************************/
int main(int argc, char **argv)
{
    int nt_palavras;              /* total number of words in input file */
    int n_palavras;               /* number of distint words in input file */
    t_tabela tabela;              /* table holding the structure */

    /* default initialization for alfabetic order and ascending */
    enum sort_criteria criterio = alphabetic;
    enum sort_order sentido  = ascending;
    char *ficheiro = argv[1];


    nt_palavras = AlocaTabelaPalavras(&tabela, ficheiro);
    printf("Total number of words: %d\n", nt_palavras);

    n_palavras = PreencheTabelaPalavras(&tabela, ficheiro);
    printf("Number of different words = %d\n", n_palavras);


    argv++;                       /* increments index of argv to point to the
                                second argument */
    while (*(++argv)) {
        if (strcmp(*argv, "-alfabetica") == 0)
            criterio = alphabetic;
        else if (strcmp(*argv, "-ocorrencias") == 0)
            criterio = occurrences;
        else if (strcmp(*argv, "-comprimento") == 0)
            criterio = length;
        else if (strcmp(*argv, "-a") == 0)
            sentido = ascending;
        else if (strcmp(*argv, "-d") == 0)
            sentido = descending;
        else {
            fprintf(stderr, "Wrong arguments\n");
            exit(3);
        }
    }

    OP_CNT = 0;
    if ((criterio == alphabetic) && (sentido == ascending)) {

        /*  Call the sorting function using as argument the
            appropriate comparison function selected by user option */

        /*==== TODO ====*/
        sort( (Item) tabela, 0, n_palavras - 1, lessAlfabetica );
        /* -- sort(....); -- */

    }
    else if((criterio == alphabetic) && (sentido == descending)){

    }
    else if((criterio == occurrences) && (sentido == ascending)){

    }
    else if((criterio == occurrences) && (sentido == descending)){

    }
    else if( (criterio == length) && (sentido == ascending)){

    }
    else if((criterio == length) && (sentido == descending)){

    }

    /*TALVEZ POR AQUI CASO NAO ACONTECA NADA MAS COMO JA SE INICIOA CRITERIO E SENTIDO TUDO FIXE!*/
    
    /* other user options */
        /*==== TODO ====*/

    /* ---------------------------------------- */
    printf("Accesses count for sort: %d\n", OP_CNT);

    EscreveFicheiro(&tabela, ficheiro, n_palavras);
/*  printf("Number of different words: %d\n", n_palavras);  */

    /* -- Insert code to call functions to free allocated memory -- */
    LibertaTabelaPalavras(&tabela, n_palavras);

    /*==== TODO ====*/

    /* ------------------------------------------------------------ */

    return 0;
}
