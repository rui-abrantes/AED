/******************************************************************************
 *
 * File Name: p2-pub.c
 *	      (c) 2019 AED
 * Author:    Luis Miguel Silveira & AED Team
 * Revision:  11 Oct 2019
 *
 * NAME
 *     p2-pub.c - testing basic functionaloty
 *
 * SYNOPSIS
 *     #include <stdlib.h>
 *     #include <stdio.h>
 *
 * DESCRIPTION
 *
 *
 * DIAGNOSTICS
 *
 *****************************************************************************/


#include <stdio.h>
#include <stdlib.h>

// COMPLEXIDADE DESTE PROGRAMA SERIA X*O(1) + O ( N^2 ) + ( O ( N^2 ) + O ( N ) ) + O ( N ) = O ( N^2 )

double func(int **data, int M, int N)
{
  double res = 0, *vetor;
  int i,j;

  vetor = (double * ) malloc((M) * sizeof(double));
  for(i = 0; i<M; i++)
    vetor[i] = 0;

  for(i = 0; i< M; i++){
    for(j = 0; j< N; j++){
      vetor[i] += data[i][j]; 
    }
    vetor[i] = vetor[i] / N;
  }

  for(i = 0; i< M; i++){
    if(res < vetor[i])
      res = vetor[i];
  }
  /* required functionality to be implemented here ... */
  free(vetor);
  return(res);
}


int main(int argc, char *argv[])
{
  int i, j, M = 0, N= 0, **data = NULL;
  double result = 0;
  FILE *fp;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s filename\n", argv[0]);
    exit(1);
  }

  fp = fopen(argv[1], "r");
  if (fp == (FILE*) NULL) {
    fprintf(stderr, "Could not open filename %s.  Exiting...\n", argv[1]);
    exit(1);
  }

  /* read M */
  fscanf(fp, "%d", &M );

  if (M <= 0) {
    fprintf(stderr, "M must be positive (%d).  Exiting...\n", M);
    exit(1);
  }

  /* read N */
  fscanf(fp, "%d", &N);

  if (N <= 0) {
    fprintf(stderr, "N must be positive (%d).  Exiting...\n", N);
    exit(1);
  }
  /* allocate memory for M lines of N additional numbers */
  data = (int ** ) malloc ( (M) * sizeof(int *) );
  for ( i = 0; i < M; i++) {
    data[i] =  (int *) malloc ( (N) * sizeof(int) );
    /* now read the numbers from the file, line by line*/
    for ( j = 0; j < N; j++) {
      data[i][j] = 0;
      fscanf(fp, "%d", &data[i][j] );
    }
    // TODO SOMETHING
  }

  /* close the input file */
  fclose(fp);

  /* Now call func(...) to determine ... */
  result = func(data, M, N);

  /* print the computed result */
  printf("result:  %lf \n", result);

  /* free memory */
  for ( i = 0; i < M; i++)
    free(data[i]);
  free(data);

  exit(0);
}
