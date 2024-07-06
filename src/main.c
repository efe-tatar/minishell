#include "../inc/lex.h"


int main(int argc, char **argv)
{
    if(argc < 2) exit(-1);

    printf("%s\n\n", argv[1]);

    dyn_arr *arr = lex(argv[1]);
    struct token *t = arr->arr;

    for(int i = 0 ; i < arr->size ; i++)
    {
        printf("%s\n", (t+i)->lexeme);
    }

    return 0;
}