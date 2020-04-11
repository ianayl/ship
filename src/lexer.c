#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEXER_TOKEN_UNIT_SIZE 7
/* TODO optimize this number */

/*
 * lexes the input string and replaces the output variable
 * with an array of strings of each individual token on its
 * own. Then returns the number of tokens lexed. self reminder
 * to free the memory after you're done lol
 */
int lexer (char* input, char*** output)
{
        /* make temp. list to fill */
        char** res = malloc(sizeof(char *)); /* space for one token */
        int token_id = 0; /* which token code is currently on */
        int token_maxsize = 0; /* how much memory the token has right now */
        int token_len = 0; /* actual index of the string the token is at */

        /* for every char in input */
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
                                res[token_id] = realloc(res[token_id],
                                                        token_maxsize
                                                        * sizeof(char));
                        }
                        /* fill token with char from input */
                        res[token_id][token_len] = input[i];
                        token_len++;
                }
        }

        /* replaces the variable provided with result */
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
        free(res);

        /* 
         * note to self: reminder to only lex upon these characters:
         * - literal space - CHECK
         * - enter
         * - "
         * - '
         * - ()
         * - probably more
         */
}
