#include "../inc/exe.h"
#include "../inc/lex.h"

#define COMMAND_BUFFER_SIZE 500

void free_dyn_arr(dyn_arr *arr);

int main(int argc, char **argv){

    char buffer[COMMAND_BUFFER_SIZE];

    dyn_arr *arr = NULL;
    
    while(1)
    {
        getcwd(buffer, COMMAND_BUFFER_SIZE);
        write(1, "\033[34m", 6);
        write(1, buffer, strlen(buffer));
        write(1, "\033[37m", 6);
        write(1, "$ ", 3);

        int n = read(0, buffer, COMMAND_BUFFER_SIZE);
        buffer[n] = '\0';
        printf("%s", buffer);

        arr = lex(buffer);

        free_dyn_arr(arr);
        arr = NULL;
    }

}

void free_dyn_arr(dyn_arr *dyn){
    for(int i = 0 ; i < dyn->size ; i++){
        free((dyn->arr+i)->lexeme);
    }
    free(dyn->arr);
    free(dyn);
}