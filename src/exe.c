#include "../inc/exe.h"

/**
 *
 */
int execute(struct node *n)
{
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
int exec_cmd(struct cmd *n)
{

    int file_exists = access(n->cmdName, X_OK);

    // access returns 0 if successful
    if (file_exists)
        panic("Command not found, terminating process\n");

    int f = fork();

    // fork failed
    if (f < 0)
        panic("Fork failed, terminating process");

    // child process
    if (!f)
        execvp(n->cmdName, n->args);

    // parent process
    if (f)
    {
        int status;
        int w = wait(&status);

        if (w == -1)
        {
            exit(-1);
        }
        if (WIFEXITED(status))
            return WEXITSTATUS(status);
        else
            return -1;
    }
}

/**
 *
 */
int exec_pipe(struct pip *n)
{

    /* establishes pipe */
    int fd[2];
    
    if (pipe(fd) == -1)
    {
        panic("Pipe failed, terminating process\n");
    }

    pid_t pid_1 = fork();

    if (pid_1 == -1)
    {
        panic("Failed when forking, terminating process\n");
    }

    if (pid_1 == 0) // manages the execution of the left node
    {
        close(fd[0]);       // close read-end of the pipe
        dup2(fd[1], 1);     // call to use write end of the pipe as std out
        close(fd[1]);       // recommended by chatgpt
        execute(n->leftNode); // execution continues
        exit(0);
    }

    pid_t pid_2 = fork();

    if (pid_2 == -1)
    {
        panic("Failed when forking, terminating process\n");
    }

    if (pid_2 == 0) // manages the execution of the right node
    {
        close(fd[1]);       // close write-end of the pipe
        dup2(fd[0], 0);     // call to use write end of the pipe as std out
        close(fd[0]);       // recommended by chatgpt
        execute(n->rightNode); // execution continues
        exit(0);
    }

    close(fd[0]);
    close(fd[1]);

    waitpid(pid_1, NULL, 0);
    waitpid(pid_2, NULL, 0);

    return 0;
}

/**
 *
 */
int exec_sep(struct sep *n)
{
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