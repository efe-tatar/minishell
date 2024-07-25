#include "../inc/util.h"

void panic(char *msg){
    write(1, msg, strlen(msg));
    exit(-1);
}