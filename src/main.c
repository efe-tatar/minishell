#include "../inc/exe.h"


int main(int argc, char **argv)
{    
    int status;

    struct cmd cat;
    cat.cmdName = "bin/cat";
    cat.type = cmd;
    char *args[] = {"cat", "file.txt", NULL};
    cat.args = args;

    struct cmd grep2;
    grep2.cmdName = "bin/grep2";
    grep2.type = cmd;
    char *args2[] = {"grep2", "train", NULL};
    grep2.args = args;

    struct pip pipe;
    pipe.leftNode = (struct node *)&cat;
    pipe.rightNode = (struct node *)&grep2;
    pipe.type = pip;

    status = execute((struct node *)(&pipe));

    printf("\nexit status: %d\n", status/255);
    return 0;
}