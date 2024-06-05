#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define WHILEUPPERBOUND 1000

typedef struct
{
    void *comp;

    node *next, *prev;
}node;

/*
*/
void panic(char *msg);

node* initialiseNode(void *comp);

node* enqueueNode(node *n, node *q);