#include "utilities.h"

/*
    this enum might get merged with the one in the parser.h file
*/
enum token{
    command,
    option,
    argument,
    ampersand,
    pipe,
    semicolon,
    outred
};

typedef struct{
    enum token type;
    char *value;
}entry;


/*
    main tokenization function

    tokenizes command line and returns
    a pointer to the headof a linked list
    containing token/value couples 
*/
entry* tokenize(char* line);