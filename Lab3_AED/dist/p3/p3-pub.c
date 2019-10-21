/******************************************************************************
 *
 * File Name: p3-pub.c
 *	      (c) 2019 AED
 * Author:    Luis Miguel Silveira & AED Team
 * Revision:  15 Oct 2019
 *
 * NAME
 *     p3-pub.c - eiNode
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "filesys.h"

#define DEBUG 1


int main(int argc, char *argv[])
{
  int N, i, retval;
  char fid, cmd;
  int blkidx[12];
  FILE *fp;

  if (argc < 3) {
    fprintf(stderr, "Usage: %s N <diskSnapshot> \n", argv[0]);
    exit(1);
  }

  /* read memory size */
  N = atoi(argv[1]);

  /* sanity check */
  if (N <= 0) {
    fprintf(stderr, "N must be positive (%d).  Exiting...\n", N);
    exit(1);
  }

  /* initialize filesystem */
  retval = filesysInit(N);
  if (retval != 0) {
    fprintf(stderr, "Error initializing filesys.  Exiting.\n");
    exit(1);
  }

  /* open file and start reading data */
  fp = fopen(argv[2], "r");
  if (fp == (FILE*) NULL) {
    fprintf(stderr, "Could not open filename %s.  Exiting...\n", argv[2]);
    exit(1);
  }

  while (1) {
    if (feof(fp)) break;
    /* read block file information */
    fscanf(fp, " %c", &fid);
    for (i = 0; i < 12; i++) {
      fscanf(fp, "%d", &blkidx[i]);
      if (blkidx[i] == -1) {
        break;
      }
    }
    /* load file into filesys */
    retval = filesysLoadFile(fid, blkidx);
    if (retval != 0) {
      fprintf(stderr, "Error loading file into filesys.  Exiting.\n");
      exit(1);
    }
  }

  while(1) {
    retval = 0;
    fprintf(stdout, "Enter command (d, p, c, e): ");
    scanf(" %c", &cmd);
    switch(cmd) {
    case 'd':
      fprintf(stdout, "Enter file name (single char):  ");
      scanf(" %c", &fid);
      retval = filesysDeleteFile(fid);
      if (retval != 0) {
        fprintf(stderr, "Error file delete for file '%c'\n", fid);
        exit(1);
      }
      break;
    case 'p':
      retval = filesysPrint();
      if (retval != 0) {
        fprintf(stderr, "Error file disk usage printing\n");
        exit(1);
      }
      break;
    case 'c':
      /* free filesys memory */
      retval = filesysClear();
      if (retval != 0) {
        fprintf(stderr, "Error clearing filesys.  Exiting.\n");
        exit(1);
      }
      break;
    case 'e':
      break;
    }
    if ((cmd == 'e') || retval) {
      break;
    }
  }

  /* free filesys memory */
  retval = filesysFree();
  if (retval != 0) {
    fprintf(stderr, "Error clearing filesys.  Exiting.\n");
    exit(1);
  }


  /* close input file */
  fclose(fp);
  exit(0);

}


