/******************************************************************************
* (c) 2010-2019 AED Team
* Last modified: abl 2019-03-01
*
* NAME
*   palTab.c
*
* DESCRIPTION
*   Main program for unique word finding with tables
*
* COMMENTS
*   Code variant for distribution
******************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX_STR 100

typedef struct _st_texto {
    int  n_total_palavras;      /* total number of words */
    int  n_dist_palavras;       /* number of distinct words*/
    char **palavras;            /* Table of strings for words */
    int  *ocorrencias;          /* Table of integers counting occurrence */
} st_texto;


/******************************************************************************
* LePalavra()
*
* Arguments: f - pointer to file where word will be read
* Returns:  pointer to word just read
* Side-Effects: none
*
* Description:
*   Return pointer to local buffer with word, or NULL if file read failed
*   Maximum word size MAX_STR
*****************************************************************************/
char *LePalavra ( FILE *f )
{
    static char palavra[MAX_STR];       /* note static local buffer returned */

    if ( fscanf ( f, "%s", palavra ) ==1 )
        return (palavra);
    else
        return ((char *) NULL);
}


/******************************************************************************
* AbreFicheiro()
*
* Arguments: nome - pointer to string holding name of file to open
*            mode - pointer to string with 'r'/'w' etc mode for file open
* Returns: pointer to opened file
* Side-Effects: exits if given file cannot be opened with given mode
*
* Description:
*   Open named file in requested mode, message stderr and exit if open fails 
*****************************************************************************/
FILE *AbreFicheiro ( char *nome, char *mode )
{
    FILE *fp;
    fp = fopen ( nome, mode );
    if ( fp == NULL ) {
        fprintf ( stderr, "ERROR: cannot open file '%s'\n", nome);
        exit ( 1 );                                 /* non-zero exit status */
    }
    return (fp);
}


/******************************************************************************
* AlocaTabelaPalavras()
*
* Arguments: ficheiro - pointer to string holding name of file to open
*            st_texto - pointer to structure where information will be saved
* Returns: (none)
* Side-Effects: none
*
* Description:
*   Read input file to find dimensions, allocate and initialize tables
*****************************************************************************/
void AlocaTabelaPalavras ( char *ficheiro, st_texto *t)
{
    FILE *fp;
    char *palavra;
    int i, len, n_max_caracteres = 0;

    (*t).n_total_palavras = 0;
    (*t).n_dist_palavras = 0;
    fp = AbreFicheiro ( ficheiro, "r" );
    while ( ( palavra = LePalavra ( fp ) ) != NULL ) {
        (*t).n_total_palavras++;
        len = strlen ( palavra );
        if ( len > n_max_caracteres )
            n_max_caracteres = len;
    }
    fclose ( fp );
    printf ( "Words count: %d\n", (*t).n_total_palavras );

    (*t).palavras = (char **) malloc((t->n_total_palavras) * sizeof(char *))  /* -- INSERT code for memory allocation --*/;
    if ( (*t).palavras == NULL ) {
        fprintf ( stderr, "ERROR: not enough memory available!\n" );
        exit ( 2 );
    }
    (*t).ocorrencias = (int *) malloc((t->n_total_palavras) * sizeof(int) )/* -- INSERT code for memory allocation --*/;
    if ( (*t).ocorrencias == NULL ) {
        fprintf ( stderr, "ERROR: not enough memory available!\n" );
        exit ( 4 );
    }
    for ( i = 0; i < (*t).n_total_palavras; i++ )   {
        (*t).palavras[i] = (char *) malloc((n_max_caracteres + 1) * sizeof(char ) )  /* -- INSERT code for memory allocation --*/;
        if ( (*t).palavras[i] == NULL ) {
            fprintf ( stderr, "ERROR: not enough memory available!\n" );
            exit ( 3 );
        }
        (*t).palavras[i][0] = '\0'/* -- INSERT code to initialize table of strings  --*/ ;
        (*t).ocorrencias[i] = 0 /* -- INSERT code to initialize table  of counters --*/ ;
    }
    return;
}


/******************************************************************************
* NovaPalavra()
*
* Arguments: palavra - pointer to string holding a word
*            st_texto - pointer to structure where run information is kept
* Returns:  int index of word in table
* Side-Effects: none
*
* Description:
*   Search for a word in the table. If the word is not found returns -1,
*   Otherwise returns the position of the word in the table
*****************************************************************************/
int NovaPalavra ( char *palavra, st_texto *t )
{
    printf("\n\nABCD : %s\n\n",palavra);
    int i = 0;
    while (i < t->n_dist_palavras)//mudei aqui de n_total, para n_dist
    {
        printf("\n\nABCD(2) : %s, NUMERO %d\n\n",(*t).palavras[i],i);
        if ( strcmp ( (*t).palavras[i], palavra ) == 0 ) {
            printf("\n\nABCD(4)\n");
            return (i);
        }            
        printf("\n\nABCD(3)\n");
        i++;
    }
    return (-1);
}

/*FEITO PELO GRUPO*/

void AlocaPalavra (char *palavra, int tamanho_nova_palavra, int tamanho_tabela ,st_texto * t){
    st_texto auxiliar;
    int i;
    
    auxiliar.palavras = (char **) malloc((tamanho_tabela + 1) * sizeof(char*));
    if ( auxiliar.palavras == NULL ) {
        fprintf ( stderr, "ERROR: not enough memory available!\n" );
        exit ( 3 );
    }

    auxiliar.ocorrencias = (int *) malloc((tamanho_tabela + 1) * sizeof(int));
    if ( auxiliar.ocorrencias == NULL ) {
        fprintf ( stderr, "ERROR: not enough memory available!\n" );
        exit ( 3 );
    }

    for(i=0 ; i < tamanho_tabela ; i++){
        auxiliar.palavras[i] = t->palavras[i];
        auxiliar.ocorrencias[i] = t->ocorrencias[i];
    }
    
    auxiliar.ocorrencias[tamanho_tabela] = 1;
    auxiliar.palavras[tamanho_tabela] = (char *) malloc((tamanho_nova_palavra + 1) * sizeof(char));
    strcpy(auxiliar.palavras[tamanho_tabela], palavra);

    free(t->palavras);
    free(t->ocorrencias);

    for(i=0 ; i< tamanho_tabela + 1; i++){
        t->palavras = auxiliar.palavras;
        t->ocorrencias = auxiliar.ocorrencias;
    }

}


/******************************************************************************
* PreencheTabelaPalavras()
*
* Arguments: ficheiro - pointer to string holding name of file to open
*            st_texto - pointer to structure where information will be saved
* Returns: (none)
* Side-Effects: none
*
* Description:
*
*****************************************************************************/
void PreencheTabelaPalavras ( char *ficheiro, st_texto *t )
{
    FILE *f;
    int word_index;
    char * palavras;
    int  size;
    
    (*t).n_total_palavras = 0;
    (*t).n_dist_palavras = 0;

    /*Falta por a parte de verificar se esta tudo bem*/

    t->ocorrencias = (int*) malloc((1) * sizeof(int));
    t->palavras = (char **) malloc((1) * sizeof(char*)); // vamos assumir que existe sempre pelo menos 1 palavra
    t->ocorrencias[0] = 0;

    f = AbreFicheiro ( ficheiro, "r" );
    while ( ( palavras = LePalavra ( f ) ) != NULL ) {
        t->n_total_palavras++;
        if ( ( word_index = NovaPalavra ( palavras, t ) ) == -1 ) {
            printf("\n\nPALAVRA : %s\n\n",palavras);
            //strcpy(palavras, "banana");
            size = strlen(palavras);
            AlocaPalavra (palavras,size , t->n_dist_palavras ,t);
            //strcpy ( (*t).palavras[(*t).n_dist_palavras], "banana" );
            //(*t).ocorrencias[(*t).n_dist_palavras]++;
            (*t).n_dist_palavras++;
        }
        else {
            (*t).ocorrencias[word_index]++;
        }
    }
    fclose ( f );
    return;
}


/******************************************************************************
* EscreveFicheiro()
*
* Arguments: ficheiro - pointer to string holding name of file to save
*            st_texto - pointer to structure where information is kept
* Returns: (none)
* Side-Effects: none
*
* Description:
*   Open output file, write table of words.
*****************************************************************************/
void EscreveFicheiro ( char *ficheiro, st_texto *t )
{
    FILE *f;
    char *nome;
    int i = 0;

    nome = (char *) malloc(  (strlen(ficheiro) + strlen(".palavras") + 1) * sizeof (char)) /* -- INSERT code for memory allocation,  --*/ ;
    /* including dot (.) extension and string termination, see below */
    if ( nome == NULL ) {
        fprintf ( stderr, "ERROR: not enough memory available!\n" );
        exit ( 5 );
    }
    strcpy ( nome, ficheiro );
    strcat ( nome, ".palavras" );
    f = AbreFicheiro ( nome, "w" );
    for ( i = 0; i < (*t).n_dist_palavras; i++ ) {
        fprintf ( f, "%d: %s\n", (*t).ocorrencias[i], (*t).palavras[i] );
    }
    printf ( "Count of distinct words: %d\n", (*t).n_dist_palavras );
    fclose ( f );
    free(nome);
    return;
}


/******************************************************************************
* main()
*
* Arguments: argc - counter of number of arguments in call
*            argv - pointer to array of strings holding the arguments
* Returns: exit status)
* Side-Effects: none
*
* Description:
*   Get filename, read input file and make word table, write output file
*****************************************************************************/
int main ( int argc, char **argv )
{
    int i;
    st_texto st_palavras;

    if ( argc < 2 ) {
        fprintf ( stderr, "ERROR: missing filename in argument!\n" );
        exit ( 6 );
    }

    //AlocaTabelaPalavras ( argv[1], &st_palavras );
    PreencheTabelaPalavras ( argv[1],&st_palavras );
    EscreveFicheiro ( argv[1], &st_palavras );

    for(i = 0; i< st_palavras.n_dist_palavras; i++)
        free(st_palavras.palavras[i]);

    free(st_palavras.palavras);
    free(st_palavras.ocorrencias);

    return (0);
}
