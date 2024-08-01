#include "util.h"

dyn_arr * lex(char *cmd);

#define DYN_ARR_EXT 4

dyn_arr * arr_append(dyn_arr *arr, struct token *t);

dyn_arr * token_def(dyn_arr *d_arr, char *lex, int lex_len, enum lex_type type);