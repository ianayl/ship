/* TODO FIX THIS */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEXER_TOKEN_UNIT_SIZE 8
/* TODO optimize this number */

/* 
 * @param input The string to lex
 * @param output The array of strings to fill with tokens
 * @return The number of tokens
 * Lexes a string into tokens and places the tokens in an array
 */
int lexer (char* input, char*** output)
{
        output = malloc(sizeof(char *)); /* space for one token */
        int token_num = 0; /* the token currently being used */
        int token_maxsize = 0; /* how much space token has */
        int token_len = 0; /* how long token is */

        for (int i = 0; i<strlen(input); i++) {
                if (input[i] == '#') {
                        /* comment */
                        return token_num;
                } if (input[i] == ' ' ||
                      input[i] == '\n') 
                {
                        /* new token */
                        token_num++;
                        output = realloc(output, (token_num + 1) *
                                                 sizeof(char *));
                        token_maxsize = 0;
                        token_len = 0;

                } else {
                        /* out of space */
                        if (token_len >= token_maxsize) {
                                printf("true, retard\n");
                                token_maxsize += LEXER_TOKEN_UNIT_SIZE;
                                output[token_num] = realloc(output[token_num],
                                                        token_maxsize
                                                        * sizeof(char));
                        }
                        output[token_num][token_len] = &input[i];
                        token_len++;
                }
        }

        /* returns length */
        return token_num + 1;
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
