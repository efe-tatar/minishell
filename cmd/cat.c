#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 50

int main(int argc, char **argv){

    int fd = 0;

    if(argc >= 2){
        fd = open(argv[1], O_RDONLY);
        if(fd == -1){
            write(2, "Cat has not been able to open the given file\n", 46);
            exit(-1);
        }
    }

    int n;
    char buffer[BUFFER_SIZE];
    while((n = read(fd, buffer, BUFFER_SIZE)) > 0){
        write(1, buffer, n);
    }

    char eof = EOF;

    write(1, &eof, 1);
    
    if(fd) close(fd);

    return 0;
}