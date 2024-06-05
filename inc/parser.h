#include "tokenizer.h"

enum nodeType{
    command,
    pipe,
    ampersand,
    semicolon,
    outred
};

// compiler autocompletes nodeType to enum nodeType ?
struct node{
    nodeType type;
};

struct optionNode{
    nodeType type;
};

struct argumentNode{
    nodeType type;
};

struct commandNode{
    nodeType type;

    struct optionNode *opt;
    struct argumentNode *arg;
};

struct pipeNode{
    nodeType type;

    struct node *input;
    struct node *output;
};

struct ampersandNode{
    nodeType type;

    struct node *sub;
};

struct semicolonNode{
    nodeType type;

    struct node *sub1;
    struct node *sub2;
};

struct outputRedNode{
    nodeType type;

    struct node *sub;
};






