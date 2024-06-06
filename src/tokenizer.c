#include "../inc/tokenizer.h"

entry* initialiseToken(enum token type, char *value)
{
    if(value == NULL)
        panic("cannot initialise token: value is missing");

    entry *newEntry = NULL;
    newEntry = malloc(sizeof(entry));
    if(newEntry == NULL)
        panic("cannot initialise token: failed to allocate memory for node");
    
    newEntry->type = type;
    newEntry->value = malloc(sizeof(char) * strlen(value) + 1);
    if(newEntry->value == NULL)
    {
        free(newEntry);
        panic("cannot initialise token: failed to allocate memory for value");
    }

    return newEntry;
}

entry* tokenize(char* line)
{
    entry *a, *b;
    a = initialiseToken(pipe, "pipe token");
    b = initialiseToken(ampersand, "ampersand token");

    node *q = NULL;
    q = enqueueNode(a, q);
    q = enqueueNode(b, q);

    return NULL;
}