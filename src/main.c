#include "../inc/lex.h"
#include "../inc/exe.h"


int main(int argc, char **argv)
{
    /*if(argc < 2) exit(-1);

    printf("%s\n\n", argv[1]);

    dyn_arr *arr = lex(argv[1]);
    struct token *t = arr->arr;

    for(int i = 0 ; i < arr->size ; i++)
    {
        printf("%s\n", (t+i)->lexeme);}*/

    
    int status;

    struct cmd n;
    n.cmdName = malloc(50);
    strcpy(n.cmdName, "bin/grep");
    n.type = cmd;
    n.args = malloc(4 * sizeof(char*));
    n.args[0] = "grep";
    n.args[1] = "hello";
    n.args[2] = "file.txt";
    n.args[3] = NULL;

    struct cmd n2;
    n2.cmdName = malloc(50);
    strcpy(n2.cmdName, "bin/ls");
    n2.type = cmd;
    n2.args = malloc(2 * sizeof(char*));
    n2.args[0] = "ls";
    n2.args[1] = NULL;

    struct sep s;
    s.type = sep;
    s.leftNode = (struct node *)&n;
    s.rightNode = (struct node *)&n2;

    status = execute((struct node *)(&s));

    printf("\nexit status: %d\n", status/255);


    return 0;
}