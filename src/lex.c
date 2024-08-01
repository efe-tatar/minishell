#include "../inc/lex.h"

dyn_arr * arr_append(dyn_arr *d_arr, struct token *t)
{
    /* may expand array by DYN_ARR_EXT */
    /* append to & return dyn arr */

    if(!d_arr) exit(-1);
    if(d_arr->cap == d_arr->size)
    {
        d_arr->arr = realloc(d_arr->arr, (d_arr->cap + DYN_ARR_EXT) * sizeof(struct token));
        
        if(!d_arr->arr) exit(-1);
        d_arr->cap += DYN_ARR_EXT;
    }

    struct token *tok = d_arr->arr;

    *(tok + d_arr->size) = *t; 
    d_arr->size++;

    return d_arr;
}

dyn_arr * token_def(dyn_arr *d_arr, char *lex, int lex_len, enum lex_type type)
{
    /* init token */
    /* append to & return dyn arr */

    if(!d_arr) exit(-1);
    if(!lex) exit(-1);

    struct token *t = NULL;
    t = malloc(sizeof(struct token));
    if(!t) exit(-1);

    t->lexeme = NULL;
    t->lexeme = malloc(lex_len+1);
    if(!t->lexeme) exit(-1);
    strncpy(t->lexeme, lex, lex_len);
    t->lexeme[lex_len] = '\0';

    t->type = type;
    
    return arr_append(d_arr, t);
}



dyn_arr * lex(char *cmd)
{
    /* return lexems */

    char whitespace[] = " \n\t\r\v\f";

    dyn_arr *arr = NULL;
    arr = malloc(sizeof(dyn_arr));
    if(!arr) exit(-1);
    arr->arr = NULL;
    arr->cap = 0;
    arr->size = 0;
    
    int j;
    for(int i = 0 ; i < strlen(cmd) ;)
        switch (*(cmd+i))
        {
            case ' ':
            case '\n':
            case '\t':
            case '\r':
            case '\v':
            case '\f':
                i++;
                continue; 
                break;
            
            case '|':
            case ';':
            case '&':
                arr = token_def(arr, cmd+i, 1, OP);
                i++;
                continue;
                break;
            
            case '-':
                j = 1;
                for(j;;j++)
                {
                    if(cmd[i+j] < 33) break;
                }
                if(j-1)
                {
                    token_def(arr, cmd+i+1, j-1, OPT);
                    i+=j+1;
                }else{
                    i++;
                }
                continue;
                break;
            
            // single/double quotes
            case 34:
            case 39:
                // ' h e l l o '
                // i 1 2 3 4 5 6
                j = 1;
                for(j;;j++)
                {
                    if(cmd[i+j] == cmd[i]) break;
                }
                if(j-1)
                {
                    token_def(arr, cmd+i+1, j-1, WORD);
                    i+=j+1;
                }else{
                    i+=2;
                }
                continue;
                break;

            default:
                j = 0;
                for(j;;j++)
                {
                    if(cmd[i+j] < 33) break;
                }
                token_def(arr, cmd+i, j, WORD);
                i+=j+1;
                continue;
                break;
        }

    printf("size arr:\t%d\n", arr->size);

    return arr;

}