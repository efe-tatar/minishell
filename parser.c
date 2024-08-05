#include "../inc/parser.h"





struct node * buildop(struct token *token){

    if(token == NULL) panic("err::empty token\n");

    if(token->lexeme == NULL) panic("err::empty lexeme\n");

    if(token->type != OP) panic("err:unexpected token");

    if( ! strcmp(token->lexeme, "&") )
    {
        struct amp *node = NULL;

        node = malloc(sizeof(struct amp));

        if(node == NULL) panic("err::mem alloc");

        node->node = NULL;
        
        node->type = amp;

        return (struct node *)node;
    }
    else if( ! strcmp(token->lexeme, "|") || ! strcmp(token->lexeme, ";") )
    {
        struct pip *node = NULL;

        node = malloc(sizeof(struct pip));

        if(node == NULL) panic("err::mem alloc");

        node->leftNode = NULL; node->rightNode = NULL;

        node->type = strcmp(token->lexeme, "|") ? sep : pip;

        return (struct node * node);
    }

    panic("err::token lexeme\n");
}


struct node * buildcommand(){
    
}



