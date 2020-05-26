
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEXER_TOKEN_UNIT_SIZE 7
/* TODO optimize this number */

/* 
 * Lexes a string into tokens and places the tokens in an array
 */
int lexer (char* input, char*** output)
{
        output = malloc(sizeof(char *)); /* space for one token */
        int token_id = 0; /* the token currently being used */
        int token_maxsize = 0;
        int token_len = 0;

        for (int i = 0; i<strlen(input); i++) {
                if (input[i] == '#') {
                        /* comment */
                        return token_id;
                } if (input[i] == ' ' ||
                      input[i] == '\n') 
                {
                        /* space / end of line */
                        token_id++;
                        output = realloc(output, (token_id + 1) *
                                                 sizeof(char *));
                        token_maxsize = 0;
                        token_len = 0;

                } else {
                        if (token_len >= token_maxsize) {
                                printf("true, retard\n");
                                token_maxsize += LEXER_TOKEN_UNIT_SIZE;
                                output[token_id] = realloc(output[token_id],
                                                        token_maxsize
                                                        * sizeof(char));
                        }
                        output[token_id][token_len] = &input[i];
                        token_len++;
                }
        }

        /* returns length */
        return token_id + 1;
}

/* For debug only, delete when done */
int main (int argc, char** argv)
{
        if (argc < 2) {
                printf("nothing to lex.\n");
                return 1;
        }

        char** g_res;
        printf("does line 64 complete fine?\n");
        int len = lexer(argv[1], &g_res);
        printf("line 64 completes fine.\n");
        printf("%d\n", len);
        for (int i = 0; i<len; i++)
                printf("%s$\n", g_res[i]);
        free(g_res);
}
