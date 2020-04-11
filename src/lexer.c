#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEXER_TOKEN_UNIT_SIZE 7
/* TODO optimize this number */

int lexer (char* input, char*** output)
{
        char** res = malloc(sizeof(char *)); /* one token */
        int token_id = 0;
        int token_maxsize = 0;
        int token_len = 0;

        for (int i = 0; i<strlen(input); i++) {
                if (input[i] == ' ' ||
                    input[i] == '\n') 
                {
                        /* handle new token */
                        /* empty token signifies end */
                        token_id++;
                        res = realloc(res, (token_id + 1) * sizeof(char *));
                        token_maxsize = 0;
                        token_len = 0;

                } else {
                        /* if out of space */
                        if (token_len >= token_maxsize) {
                                token_maxsize += LEXER_TOKEN_UNIT_SIZE;
                                /* TODO might need to watch for realloc and a 
                                 * new pointer position here */
                                res[token_id] = realloc(res[token_id],
                                                        token_maxsize * sizeof(char));
                        }
                        /* fill token with char from input */
                        res[token_id][token_len] = input[i];
                        token_len++;
                }
        }

        *output = res;
        /* returns length */
        return token_id + 1;
}

/* For debug only */
int main (int argc, char** argv)
{
        if (argc < 2) {
                printf("nothing to lex.\n");
                return 1;
        }

        char** res;
        int len = lexer(argv[1], &res);
        for (int i = 0; i<len; i++)
                printf("%s$\n", res[i]);
        /* 
         * note to self: reminder to only lex upon these characters:
         * - literal space
         * - enter
         * - "
         * - '
         * - ()
         * - probably more
         */
}
