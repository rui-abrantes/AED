#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"
#include "queue.h"



Queue * QueueNew(){
    Queue * Node = (Queue *) malloc( sizeof(Queue ) );
    if(Node == NULL){
        printf("Couldn't allocate memory for the Queue Node");
        exit(1);
    }
    Node->last = NULL;
    Node->first = NULL;

    return Node;
}

Element * GetFirst(Queue* Node){
    Element * OldFirst = Node->first;
    Node->first = Node->first->next;
    
    return OldFirst;
}

void InsertLast(Queue* Queue, Node* Node, int nivel){ 

    Element * element = (Element *) malloc(sizeof(Element ));
    if(element == NULL){
        printf("Couldnt allocate memory for element");
        exit(1);
    }

    element->level = nivel;
    element->node = Node;
    element->next = NULL;
    
    if(Queue->last != NULL){
        Queue->last->next = element;
        Queue->last = element;
    }
    else
        Queue->last = element;
}

void FreeQueue(Queue * Node){
    free(Node);
}

void FreeElementList(Element * element){
    Element * auxiliar;

    while(element != NULL){
        auxiliar = element->next;
        free(element);
        element = auxiliar;
    }

}
