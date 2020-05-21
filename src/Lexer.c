#include <stdio.h>

#define LEXER_TOKEN_UNIT_SIZE 8
/* TODO optimize this number */

/* 
 * Lexes a string into tokens and places them into a TokenList
 */
int lexer ( char* input)
{
        return -1;
}

/* For debug only, delete when done */
int main (int argc, char** argv)
{
        if (argc < 2) {
                printf("nothing to lex.\n");
                return 1;
        }

        printf("commencing operation");
        int len = lexer( argv[1]);
}
