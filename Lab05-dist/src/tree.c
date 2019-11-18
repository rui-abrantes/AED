/******************************************************************************
 *
 * File Name: tree.c
 *	      (c) 2010 AED
 * Author:    AED team
 * Revision:  v2.3 ACR
 *            v3.0 AED Team Out 2013
 *            v4.0 AED Team, Nov 2019
 *
 * NAME
 *     Tree - different forms of tree sweep
 *
 * SYNOPSIS
 *     #include <stdlib.h>
 *     #include <stdio.h>
 *     #include <malloc.h>
 *
 * DESCRIPTION
 *		implements tree auxiliary functions
 * DIAGNOSTICS
 *
 *****************************************************************************/

#include <limits.h>
#include "tree.h"
#include "queue.h"


struct _Node {
  int value;
  struct _Node *left, *right;
};


/******************************************************************************
 * AllocNode()
 *
 * Arguments: (none)
 * Returns: new node
 * Side-Effects: none
 *
 * Description: allocates space for a new node
 *
 *****************************************************************************/

Node *AllocNode() {
  return ((Node *) malloc(sizeof(Node)));
}


/******************************************************************************
 * NewNode()
 *
 * Arguments: integer
 * Returns: new node
 * Side-Effects: none
 *
 * Description: creates a new node with a integer value
 *
 *****************************************************************************/

Node *NewNode(int num)
{
  Node *aux;

  if (num==-1)
    return NULL;

  aux = AllocNode();
  aux->value = num;
  aux->right = aux->left = NULL;

  return aux;
}


/******************************************************************************
 * Construct()
 *
 * Arguments: input file and filename
 * Returns: pointer to root node of the tree
 * Side-Effects: none
 *
 * Description: constructs a tree reading integer numbers from file
 *
 *****************************************************************************/

Node *Construct(FILE *fp, char * filename)
{
  Node *nodeRoot;
  int num;

  if (fscanf(fp,"%d", &num) == EOF)  {
    fprintf(stderr,
            "File %s has an insufficient number of values.  Please correct.\n",
            filename);
    exit(0);
  }

  if ((nodeRoot = NewNode(num)) != NULL) {
    /* links to child */
    nodeRoot->left  = Construct(fp, filename);
    nodeRoot->right = Construct(fp, filename);
  }

  return nodeRoot;
}


/******************************************************************************
 * FreeTree()
 *
 * Arguments: node - a tree root
 *
 * Returns: void
 * Side-Effects: none
 *
 * Description: frees the tree
 *
 *****************************************************************************/

void FreeTree(Node * root)
{
  if (root != NULL) {
    FreeTree(root->left);
    FreeTree(root->right);
    free(root);
  }
}


/******************************************************************************
 * spaces()
 *
 * Arguments: n - number of spaces
 * Returns: void
 * Side-Effects: none
 *
 * Description: prints n spaces
 *
 *****************************************************************************/

void spaces(int n)
{
  int i;

  for (i = 0; i < n; i++)
    printf("  ");
  return;
}

void tabs(int n)
{
  int i;

  for (i = 0; i < n; i++)
    printf("\t");
  return;
}


/******************************************************************************
 * PreFixed()
 *
 * Arguments: root - root of the tree
 *	      n - height of the tree
 * Returns: void
 * Side-Effects: none
 *
 * Description: prints the tree in the PreFix format
 *
 *****************************************************************************/

void PreFixed(Node *root, int n)
{
  if (root != NULL) {
    spaces(n);
    printf("%d\n", root->value);
    PreFixed(root->left, n + 1);
    PreFixed(root->right, n + 1);
  }

  return;
}


/******************************************************************************
 * InFixed()
 *
 * Arguments: root - root of the tree
 *	      n - height of the tree
 * Returns: void
 * Side-Effects: none
 *
 * Description: prints the tree in the InFix format
 *
 *****************************************************************************/

void InFixed(Node *root, int n)
{ 
  if (root != NULL) {
    InFixed(root->left, n + 1);
    spaces(n);
    printf("%d\n", root->value);
    InFixed(root->right, n + 1);
  }
  /* Insert code */

  return;
}


/******************************************************************************
 * PosFixed()
 *
 * Arguments: root - root of the tree
 *	      n - height of the tree
 * Returns: void
 * Side-Effects: none
 *
 * Description: prints the tree in the PosFix format
 *
 *****************************************************************************/

void PosFixed(Node *root, int n)
{
  if (root != NULL) {
    PosFixed(root->left, n + 1);
    PosFixed(root->right, n + 1);
    spaces(n);
    printf("%d\n", root->value);
  }
  /* Insert code */

  return;
}


/******************************************************************************
 * sweepDepth()
 *
 * Arguments: root - root of the tree
 *	      n - height of the tree
 * Returns: void
 * Side-Effects: none
 *
 * Description: prints the tree in the depthfirst format
 *
 *****************************************************************************/

void sweepDepth(Node *root, int n)
{
  if (root != NULL) {
    tabs(n);
    printf("%d\n", root->value);
    sweepDepth(root->left, n + 1);
    sweepDepth(root->right, n + 1);
  }

  return;
}


/******************************************************************************
 * sweepBreadth()
 *
 * Arguments: root - root of the tree
 *
 * Returns: void
 * Side-Effects: none
 *
 * Description: prints the tree in the Breathfirst format
 *
 *****************************************************************************/

void sweepBreadth(Node *root)
{
  Queue * queue = QueueNew();
  Element * auxiliar = NULL, * elementFree = NULL, * firstElement = NULL;

  if(root != NULL){
    InsertLast(queue,root,0 );
    queue->first = queue->last;
    elementFree = queue->first;
  }
  else{
    printf("There's noo root to do the sweepBreadth");
    return;
  }

  while(1){

    while(queue->first != NULL){

      auxiliar = GetFirst(queue);
      if(auxiliar == NULL)
        break;

      if(auxiliar->node->left != NULL &&  auxiliar->node->left->value != -1){
        InsertLast(queue, auxiliar->node->left, auxiliar->level + 1);
      }
      if(auxiliar->node->right != NULL &&  auxiliar->node->right->value != -1 )
        InsertLast(queue, auxiliar->node->right, auxiliar->level + 1);

      firstElement = auxiliar;

    }
    queue->first = firstElement->next;

    if(firstElement->next == NULL)
      break;
  }

  queue->first = elementFree;

  while(queue->first != NULL){
    auxiliar = GetFirst(queue);
    spaces(auxiliar->level);
    printf("%d\n", auxiliar->node->value);
  }
  
  FreeElementList(elementFree);
  FreeQueue(queue);  
  /* Insert code */

  return;
}

/******************************************************************************
 * IsTreeOrdered()
 *
 * Arguments: node - a tree root
 *
 *
 * Returns: Boolean (TRUE if the tree is ordered, FALSE otherwise)
 * Side-Effects: none
 *
 * Description: checks if a tree is ordered
 *
 *****************************************************************************/

Boolean isTreeOrdered(Node * root)
{
  if (root != NULL) {
    if(root->left != NULL){
      if(root->value <  root->left->value)
        return FALSE;
    }
    if(root->right != NULL){
    if(root->value >  root->right->value)
      return FALSE;
    }
    if(!(isTreeOrdered(root->left)))
      return FALSE;
    if(!(isTreeOrdered(root->right)))
      return FALSE;
  }

  return TRUE;
}


/******************************************************************************
 * IsTreeBalanced()
 *
 * Arguments: node - a tree root
 *
 *
 * Returns: Boolean (TRUE if the tree is AVL balanced, FALSE otherwise)
 * Side-Effects: none
 *
 * Description: checks if a tree is AVL balanced
 *
 *****************************************************************************/

Boolean isTreeBalanced(Node * root)
{

  if (root != NULL) {

    if(altura(root->left) != altura(root->right))
      return FALSE;
    isTreeOrdered(root->left);
    if(altura(root->left) != altura(root->right) ) 
      return FALSE;
    isTreeOrdered(root->right);
  }

  return TRUE;
}


int altura(Node *h)
{
int u, v;
if (h == NULL) return 0;
u = altura(h->left); v = altura(h->right);
if (u > v) return u+1; else return v+1;
}




