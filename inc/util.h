
#ifndef UTIL_H
#define UTIL_H
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include<sys/wait.h>

void panic(char *msg);

enum lex_type{
    WORD,   // command, argument
    OPT,    // option
    OP      // operation
};

struct token{
    enum lex_type type;
    char *lexeme;
};

typedef struct __dyn_array_struct__{
    int size;
    int cap;
    struct token *arr;
}dyn_arr;


#define DYN_ARR_EXT 4
dyn_arr * arr_append(dyn_arr *arr, struct token *t);


enum nodeType{
    cmd,
    pip,
    amp,
    sep
};

struct node{
    enum nodeType type;
};

struct cmd{
    enum nodeType type;
    char *cmdName;
    char **args;
};

struct pip{
    enum nodeType type;
    struct node *leftNode;
    struct node *rightNode;
};

struct sep{
    enum nodeType type;
    struct node *leftNode;
    struct node *rightNode;
};

struct amp{
    enum nodeType type;
    struct node *node;
};


#endif