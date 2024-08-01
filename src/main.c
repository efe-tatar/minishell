#include "../inc/exe.h"


int main(int argc, char **argv)
{    
    int status;

    struct cmd cat;
    cat.cmdName = "bin/cat";
    cat.type = cmd;
    char *args[] = {"cat", "file2", NULL};
    cat.args = args;

    struct cmd grep2;
    grep2.cmdName = "bin/grep2";
    grep2.type = cmd;
    char *args2[] = {"grep2", "file", NULL};
    grep2.args = args2;

    struct cmd grep3;
    grep3.cmdName = "bin/grep2";
    grep3.type = cmd;
    char *args3[] = {"grep2", "love", NULL};
    grep3.args = args3;

    struct pip pipe;
    pipe.leftNode = (struct node *)&cat;
    pipe.rightNode = (struct node *)&grep2;
    pipe.type = pip;

    struct pip pipe2;
    pipe2.leftNode = (struct node *)&pipe;
    pipe2.rightNode = (struct node *)&grep3;
    pipe2.type = pip;

    status = execute((struct node *)(&pipe2));

    printf("\nexit status: %d\n", status/255);
    return 0;
}