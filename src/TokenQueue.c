#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Token
{
        char* val;
        /* TODO add type enum */

} Token;

/* A queue of tokens */
typedef struct TokenQueue
{
        Token* queue;
        unsigned len;
} TokenQueue;

TokenQueue TokenQueue_new ()
{
        TokenQueue res;

        res.len = 0;
        res.queue = 0;

        return res;
}

void TokenQueue_push (TokenQueue *dest, char* v)
{
        /* TODO reminder to accomidate for types */
        if (dest->len == 0)
                dest->queue = malloc(sizeof(Token));
        else
                dest->queue = realloc(dest->queue, (dest->len + 1)
                                                   * sizeof(Token));
        /* assuming sizeof(char) = 0 */
        dest->queue[dest->len].val = malloc(strlen(v) + 1);
        strcpy(dest->queue[dest->len].val, v);

        dest->len ++;
}

char* TokenQueue_getVal (TokenQueue *dest, unsigned index)
{
        if (index >= dest->len || index < 0)
                return 0;
        return dest->queue[index].val;
};

void TokenQueue_destroy (TokenQueue *dest)
{
        for (int i = (dest->len - 1); i >= 0; i--)
                free(dest->queue[i].val);
        free(dest->queue);
}

/* For debug only, remove when done */
int main ()
{
        TokenQueue test = TokenQueue_new();
        TokenQueue_push(&test, "abc");
        TokenQueue_push(&test, "def");
        TokenQueue_push(&test, "ghi");
        for (int i = 0; i<test.len; i++)
                printf("%s\n", TokenQueue_getVal(&test, i));
        TokenQueue_destroy(&test);
}
