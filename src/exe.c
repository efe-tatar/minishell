#include "../inc/exe.h"

/**
 * 
 */
int execute(struct node *n){
    switch (n->type)
    {
        case cmd:
            exec_cmd((struct cmd *)n);
            break;
        
        case sep:
            exec_sep((struct sep *)n);
            break;
        
        case pip:
            exec_pipe((struct pip *)n);
            break;
        
        case amp:
            break;

        default:
            panic("Node not recognised, terminating process\n");
            break;
    }
}

/**
 * 
 */
int exec_cmd(struct cmd *n){

    int file_exists = access(n->cmdName, X_OK);

    // access returns 0 if successful
    if(file_exists) panic("Command not found, terminating process\n");

    int f = fork();

    // fork failed
    if(f < 0)   panic("Fork failed, terminating process");

    // child process
    if(!f)      execvp(n->cmdName, n->args);

    // parent process
    if(f){
        int status;
        int w = wait(&status);

        if(w == -1){
            exit(-1);
        }
        if(WIFEXITED(status)) return WEXITSTATUS(status);
        else return -1;
    }
}

/**
 * 
 */
int exec_pipe(struct pip *n){

    /* establishes pipe */
    int fd[2];
    if(pipe(fd) == -1) panic("Pipe failed, terminating process\n");

    int p = fork();
    if(p == -1){
        panic("Failed when forking, terminating process\n");
    }

    if(p == 0)          // manages the execution of the left node
    {
        close(fd[0]);   // close read-end of the pipe
        close(1);       // close the std out stream
        dup(fd[1]);     // call to use write end of the pipe as std out
        return execute(n->leftNode);    // execution continues
    }

    p = fork();
    
    if(p == -1){
        panic("Failed when forking, terminating process\n");
    }

    if(p == 0)          // manages the execution of the right node
    {
        close(fd[1]);   // close write-end of the pipe
        close(0);       // close the std in stream
        dup(fd[0]);     // call to use write end of the pipe as std out
        return execute(n->leftNode);    // execution continues
    }

    return 0;
}

/**
 * 
 */
int exec_sep(struct sep *n){
    int l = execute(n->leftNode);
    int r = execute(n->rightNode);

    return l && r;
}

/**
 * 
 */
int exec_amp(struct amp *n)
{

}