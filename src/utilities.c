#include "../inc/utilities.h"

void panic(char *msg)
{
    printf("%s", msg);
    exit(-1);
}

node* initialiseNode(void *comp)
{
    if(comp == NULL)
        panic("cannot initialise node: comp is missing");
    
    node *newNode = NULL;

    newNode = malloc(sizeof(node));

    if(newNode == NULL)
        panic("cannot initialise node: failed to allocate memory");
    
    newNode->comp = comp;
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}

node* enqueueNode(node *n, node *q)
{
    if(n == NULL)
        panic("cannot enqueue node: node is missing");
    
    // q is empty so first element becomes n
    if(q == NULL)
        return n;
    
    // traversing the list with k to append node
    node *k = q;
    int i = 0;
    while(k->next != NULL && i < WHILEUPPERBOUND)
    {
        k = k->next;
        i++;
    }

    if(i == WHILEUPPERBOUND)
        panic("cannot enqueue node: loop has reached the upper bound");
    
    k->next = n;
    n->prev = k;
    return q;
}