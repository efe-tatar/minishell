#include "../inc/parse.h"

/*
parsing consists of:
1 - preparser goes through array to init corresponding nodes
2 - shunting yard implementation arranges nodes in RPN
3 - queue is traversed to build the AST
*/

