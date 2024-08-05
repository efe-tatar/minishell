#include "../inc/parser.h"





struct node * buildop(struct token *token){

    if(token == NULL) panic("err::empty token\n");

    if(token->lexeme == NULL) panic("err::empty lexeme\n");

    if(token->type != OP) panic("err:unexpected token\n");

    if( ! strcmp(token->lexeme, "&") )
    {
        struct amp *node = NULL;

        node = malloc(sizeof(struct amp));

        if(node == NULL) panic("err::mem alloc\n");

        node->node = NULL;
        
        node->type = amp;

        return (struct node *)node;
    }
    else if( ! strcmp(token->lexeme, "|") || ! strcmp(token->lexeme, ";") )
    {
        struct pip *node = NULL;

        node = malloc(sizeof(struct pip));

        if(node == NULL) panic("err::mem alloc\n");

        node->leftNode = NULL; node->rightNode = NULL;

        node->type = strcmp(token->lexeme, "|") ? sep : pip;

        return (struct node *)node;
    }

    panic("err::token lexeme\n");
}


struct node * buildcommand(struct token *token, struct token *args, int argc){
    
    if(token == NULL || args == NULL) panic("err::empty token\n");

    if(token->lexeme == NULL) panic("err::empty lexeme\n");

    if(token->type != WORD) panic("err:unexpected token\n");

    struct cmd *node = NULL;
    
    node = malloc(sizeof(struct cmd));

    if(node == NULL) panic("err::mem alloc\n");

    node->type = cmd;

    node->cmdName = NULL;

    node->cmdName = malloc(strlen(token->lexeme) + 1);

    strcpy(node->cmdName, token->lexeme);

    node->cmdName[strlen(token->lexeme)] = '\0';

    node->args = NULL;

    node->args = malloc((argc + 2) * sizeof(char *));

    if(node->args == NULL) panic("err::mem alloc\n");

    node->args[argc + 1] = NULL;

    node->args[0] = NULL;

    node->args[0] = malloc(strlen(token->lexeme) + 1);

    strcpy(node->args[0], token->lexeme); node->args[0][strlen(token->lexeme)] = '\0';

    for(int i = 1 ; i <= argc ; i++)
    {
        node->args[i] = NULL;
        node->args[i] = malloc(strlen(args[i-1]) + 1);
        if(node->args[i] == NULL) panic("err::mem alloc\n");
        strcpy(node->args[i], args[i-1]);
        node->args[i][strlen(args[i-1])] = '\0';
    }

    return (struct node *)node;
}



