/******************************************************************************
 *
 * File Name: filesys.h
 *	      (c) 2019 AED
 * Author:    Luis Miguel Silveira & AED Team
 * Revision:  15 Oct 2019
 *
 * NAME
 *     bignum.h - implementation library for handling bignums
 *
 * SYNOPSIS
 *     #include "bignum.h"
 *
 * DESCRIPTION
 *
 *
 * DIAGNOSTICS
 *
 *****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "filesys.h"

typedef struct _easy_iNode {
  char fileName;
  /* additional file info here */
  int blk[12];
} eiNode;

typedef struct BlockLoc {
  eiNode *owningFile;
  int fileblkNumber;
  /* save disk location here */
} BlockLoc;

BlockLoc *diskInfo = (BlockLoc*) NULL; /* table of disk blocks by all files */
int diskSize = -1;

#include "LinkedList.h"

LinkedList *fileList = (LinkedList*) NULL; /* list of files in filesystem */


/******************************************************************************
 * filesysInit()
 *
 * Arguments: N - size of disk in block
 * Returns: int - 0 if ok, 1 if error
 * Side-Effects: diskInfo gets allocated to size N blocks
 *
 * Description:
 *
 *****************************************************************************/

int filesysInit(int N) {

  int i;

  diskSize = N;
  diskInfo = (BlockLoc*) malloc (N * sizeof(BlockLoc));
  if (diskInfo == (BlockLoc*)NULL) {
    return (1);
  }
  for (i = 0; i < N; i++) {
    diskInfo[i].owningFile = (eiNode*) NULL;
    diskInfo[i].fileblkNumber = -1;
  }

  fileList = initLinkedList();
  if (fileList != (LinkedList*)NULL) {
    return (1);
  }

  return(0);
}


/******************************************************************************
 * filesysFreeFile()
 *
 * Arguments: vfptr - pointer to eiNode
 * Returns: none
 * Side-Effects: frees the eiNode structure
 *
 * Description:
 *
 *****************************************************************************/

void filesysFreeFile(Item item) {

  eiNode *fptr = (eiNode*) item;
  int i, blk;

  for (i = 0; i < 12; i++) {
    blk = fptr->blk[i];
    if (blk == -1)
      break;
    diskInfo[blk].owningFile = (eiNode*) NULL;
    diskInfo[blk].fileblkNumber = -1;
  }

  free(fptr);

  return;
}


/******************************************************************************
 * filesysClear()
 *
 * Arguments: none
 * Returns: Item -
 * Side-Effects: diskInfo gets cleared and the list of files is also cleared
 *
 * Description:
 *
 *****************************************************************************/

int filesysClear() {

  freeLinkedList(fileList, filesysFreeFile);
  fileList = (LinkedList*) NULL;

  return (0);
}


/******************************************************************************
 * filesysFree()
 *
 * Arguments: none
 * Returns: Item -
 * Side-Effects: diskInfo gets cleared and the list of files is also cleared
 *
 * Description:
 *
 *****************************************************************************/

int filesysFree() {

  filesysClear();

  free(diskInfo);
  diskSize = -1;

  return (0);
}


/******************************************************************************
 * filesysLoadFile()
 *
 * Arguments: fid - file identifier
 *            blk - table of possible 12 disk blocks in use by file
 * Returns: int - 0 if ok, 1 if error
 * Side-Effects: loads file into memory and adds file to list of files
 *
 * Description:
 *
 *****************************************************************************/

int filesysLoadFile(char fid, int *blk) {

  eiNode * newBlock = NULL;
  int retval = 0, i;

  newBlock = (eiNode *) malloc( sizeof(eiNode) ); // create a newblock of eiNode
  if(newBlock == NULL){
    printf("\nCould not allocate eiNode Block memory\n");
    exit(1);
  }

  newBlock->fileName = fid;

  for (i = 0; i < 12; i++) {
    newBlock->blk[i] = blk[i];
    if (blk[i] == -1) {
      break;
    }
  }

  /* INICIO DA PILHA */
  i=0;
  while(1){
    if (blk[i] == -1) {
      break;
    }
    diskInfo[ newBlock->blk[i] ].owningFile = newBlock;
    diskInfo[ newBlock->blk[i] ].fileblkNumber = i;
    i++;
  }
  /* FIM DA PILA */

  /* INICIO DA LISTA */
  
  fileList = insertUnsortedLinkedList(fileList, (Item) newBlock);

  /* FIM DA LISTA */

  /* TO BE COMPLETED */

  return (retval);
}


/******************************************************************************
 * filesysDeleteFile()
 *
 * Arguments: fid - file identifier
 *            blk - table of possible 12 disk blocks in use by file
 * Returns: int - 0 if ok, 1 if error
 * Side-Effects: loads file into memory and adds file to list of files
 *
 * Description:
 *
 *****************************************************************************/

int filesysDeleteFile(char fid) {

  eiNode * deletedBlock;
  LinkedList * auxiliar;
  auxiliar = fileList;
  int retval = 0,i = 0, counter = 0;

  while(auxiliar != NULL){
    deletedBlock = (eiNode *) getItemLinkedList(auxiliar);
    if (deletedBlock->fileName == fid){
      while(1){
        if (deletedBlock->blk[i] == -1) {
          break;
        }
        diskInfo[ deletedBlock->blk[i] ].fileblkNumber = -1;
        diskInfo[ deletedBlock->blk[i] ].owningFile = (eiNode * )NULL;
        i++;
      }
      break;
    }
    counter++;
    auxiliar = getNextNodeLinkedList(auxiliar);
  }

  printf("\n\nCOUNTER : %d\n\n", counter);

  auxiliar = fileList;

  if(counter == 0){
    fileList = deleteHeaderLinkedList(fileList, filesysFreeFile);
    return(retval);
  }

  while( counter != 1 && counter > 0){
    auxiliar = getNextNodeLinkedList (auxiliar);
    counter --;
  }

  deleteNextNodeLinkedList(auxiliar, filesysFreeFile);

  /* TO BE COMPLETED */

  return (retval);
}


/******************************************************************************
 * filesysPrint()
 *
 * Arguments: none
 * Returns: none
 * Side-Effects: none
 *
 * Description: prints state of filesystem blocks
 *
 *****************************************************************************/

int filesysPrint() {
  eiNode *fptr;
  int i, blknum;
  char fid;

  for(i = 0; i < diskSize; i++) {
    fprintf(stdout, "----");
  }
  fprintf(stdout, "\n");
  for(i = 0; i < diskSize; i++) {
    fptr = diskInfo[i].owningFile;
    if (fptr == (eiNode*) NULL)
      fid = ' ';
    else
      fid = fptr->fileName;
    fprintf(stdout, " %2c ", fid);
  }
  fprintf(stdout, "\n");
  for(i = 0; i < diskSize; i++) {
    fptr = diskInfo[i].owningFile;
    if (fptr == (eiNode*) NULL)
      blknum = 0;
    else
      blknum = diskInfo[i].fileblkNumber;
    fprintf(stdout, " %2d ", blknum);
  }
  fprintf(stdout, "\n");

  return (0);
}


