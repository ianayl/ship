#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TokenArr.h"

/* 
 * Lexes a string into tokens and places them into a TokenArr
 */
void lexer (TokenArr *dest, char* input)
{
        unsigned short str_end = 0;
        char* buf = calloc(1, 1);
        unsigned buf_len = 1;

        unsigned short in_quotes = 0;

        for (unsigned i = 0; !str_end; i++) {
                printf("%c buf:%s\n", input[i], buf);

                if (input[i] == '\0' ||
                    input[i] == '\n') {

                        /* 
                         * TODO if quotation is not finished, find
                         * a way to indicate that in the returned 
                         * TokenArr.
                         */
                        if (buf_len > 1)
                                TokenArr_push(dest, buf);
                        str_end = 1;
                        break;

                } else if (input[i] == '\"') {

                        if (in_quotes) {

                                buf_len ++;
                                buf = realloc(buf, buf_len);
                                buf[buf_len-1] = '\0';
                                buf[buf_len-2] = input[i];

                                TokenArr_push(dest, buf);
                                free(buf);
                                buf = calloc(1, 1);
                                buf_len = 1;

                                in_quotes = 0;

                        } else {

                                TokenArr_push(dest, buf);
                                free(buf);

                                buf = calloc(2, 1);
                                buf[0] = input[i];
                                buf_len = 2;

                                in_quotes = 1;
                        }

                } else if (in_quotes) {

                        buf_len ++;
                        buf = realloc(buf, buf_len);
                        buf[buf_len-1] = '\0';
                        buf[buf_len-2] = input[i];

                } else if (input[i] == ' ' ||
                           input[i] == '\t' ||
                           input[i] == '\n' ||
                           input[i] == '\v' ||
                           input[i] == '\f' ||
                           input[i] == '\r' ) {

                        if (buf_len > 1) {
                                TokenArr_push(dest, buf);
                                free(buf);
                                buf = calloc(1, 1);
                                buf_len = 1;
                        }

                } else if (input[i] == '#') {

                        if (buf_len > 1)
                                TokenArr_push(dest, buf);
                        str_end = 1;
                        break;
                        
                } else {
                        /* 
                         * I don't think expanding size by 1
                         * everytime is the best approach perf tho,
                         * might want to optimize this 
                         */
                        buf_len ++;
                        buf = realloc(buf, buf_len);
                        buf[buf_len-1] = '\0';
                        buf[buf_len-2] = input[i];
                }
        }

        free(buf);
}

/* For debug only, delete when done */
int main (int argc, char** argv)
{
        if (argc < 2) {
                printf("nothing to lex.\n");
                return 1;
        }

        TokenArr tokens = TokenArr_new();
        lexer(&tokens, argv[1]);
        for (int i = 0; i<tokens.len; i++) {
                printf("%s$\n", TokenArr_getVal(&tokens, i));
        }
        TokenArr_destroy(&tokens);
}
