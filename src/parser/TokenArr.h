#ifndef TOKENARR_H
#define TOKENARR_H

/* Stores a single token and it's type */
typedef struct Token
{
        char* val;
        /* TODO add type enum */

} Token;

/* A queue of tokens */
typedef struct TokenArr
{
        Token* queue;
        unsigned len;
} TokenArr;

TokenArr TokenArr_new ();

void TokenArr_push (TokenArr *dest, char* v);

char* TokenArr_getVal (TokenArr *dest, unsigned index);

void TokenArr_destroy (TokenArr *dest);

#endif
