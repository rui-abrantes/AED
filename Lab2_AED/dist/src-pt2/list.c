/******************************************************************************
* (c) 2010-2019 AED Team
* Last modified: abl 2019-02-28
*
* NAME
*   list.c
*
* DESCRIPTION
*   Implement general linked list functions, for use in word lists
*
* COMMENTS
*
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"


/* Linked list  */
struct _t_lista {
    Item            this;
    struct _t_lista *prox;
};


/******************************************************************************
* iniLista ()
*
* Arguments: none
* Returns: t_lista *
* Side-Effects: list is initialized
*
* Description: initializes list
*****************************************************************************/
t_lista  *iniLista(void)
{
    return NULL;
}


/******************************************************************************
* criaNovoNoLista ()
*
* Arguments: nome - Item to save in list node
* Returns: t_lista  *
* Side-Effects: none
*
* Description: creates and returns a new node that can later be added to the  <<<<<<<<<<<<<< FIX
*              list
*****************************************************************************/
t_lista  *criaNovoNoLista (t_lista* lp, Item this, int *err)
{
    /*when we got the code, the words where being put on the beginning of the list
    * we made it being put on the end of the list*/
    t_lista *novoNo, *aux = lp;

    novoNo = (t_lista*) malloc(sizeof(t_lista));
    if(novoNo!=NULL)
    {
        novoNo->this = this;
        novoNo->prox = NULL;
        if(aux == NULL){
            lp = novoNo;
        }
        else{
            while(aux->prox !=NULL)
                aux= aux->prox;
            aux->prox = novoNo;
        }

        
        *err = 0;
    } else
    {
        *err = 1;
        /*insert text about not being able to allocate memory*/
    }
    return lp;
}


/******************************************************************************
* getItemLista ()
*
* Arguments: this - pointer to element
* Returns: Item
* Side-Effects: none
*
* Description: returns an Item from the list
*****************************************************************************/
Item getItemLista (t_lista *p)
{
    return p -> this;
}


/******************************************************************************
* getProxElementoLista ()
*
* Arguments: this - pointer to element
* Returns: pointer to next element in list
* Side-Effects: none
*
* Description: returns a pointer to an element of the list
*
*****************************************************************************/
t_lista *getProxElementoLista(t_lista *p) {

    return p -> prox;
}


/******************************************************************************
* numItensNaLista ()
*
* Arguments: lp - pointer to list
* Returns:  count of the number of items in list
* Side-Effects: none
*
* Description: returns the number of items (nodes) in the list
*
*****************************************************************************/
int numItensNaLista(t_lista *lp) {
    t_lista *aux;  /* auxiliar pointers to travel through the list */
    int conta = 0;
    aux = lp;

    for(aux = lp; aux != NULL; aux = aux -> prox)
    conta++;

    return conta;
}

/******************************************************************************
* libertaLista ()
*
* Arguments: lp - pointer to list
* Returns:  (void)
* Side-Effects: frees space occupied by list items
*
* Description: free list
*
*****************************************************************************/
void libertaLista(t_lista *lp, void freeItem(Item)) {
    t_lista *aux, *newhead;  /* auxiliar pointers to travel through the list */

    for(aux = lp; aux != NULL; aux = newhead) {
        newhead = aux->prox;
        freeItem(aux->this);
        free(aux);
    }

    return;
}
/******************************************************************************
* inverteLista ()
*
* Arguments: Node1 -> pointer of the head of the list, Node2 -> pointer of the
*  previous structure
* Returns:  (t_lista*)
* Side-Effects: Recursive function and the first time its called Node2 needs 
*               to be NULL
*
* Description: Inverts the list
*
*****************************************************************************/
t_lista * inverteLista(t_lista* Node1, t_lista* Node2){
    t_lista *aux; /*it's going be pointing to the one we want to invert at the time*/

    if(Node1->prox == NULL){
        Node1->prox = Node2;
        return Node1;
    }
    aux = Node1->prox;
    Node1->prox = Node2;

    return inverteLista(aux, Node1);
}
