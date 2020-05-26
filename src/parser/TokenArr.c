#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "TokenArr.h"

TokenArr TokenArr_new ()
{
        TokenArr res;

        res.len = 0;
        res.queue = 0;

        return res;
}

void TokenArr_push (TokenArr *dest, char* v)
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

char* TokenArr_getVal (TokenArr *dest, unsigned index)
{
        if (index >= dest->len || index < 0)
                return 0;
        return dest->queue[index].val;
};

void TokenArr_destroy (TokenArr *dest)
{
        for (int i = (dest->len - 1); i >= 0; i--)
                free(dest->queue[i].val);
        free(dest->queue);
}

/*
 * Test code lol, pls ignore 
 *
 * int main ()
 * {
 *         TokenArr test = TokenArr_new();
 *         TokenArr_push(&test, "abc");
 *         TokenArr_push(&test, "def");
 *         TokenArr_push(&test, "ghi");
 *         for (int i = 0; i<test.len; i++)
 *                 printf("%s\n", TokenArr_getVal(&test, i));
 *         TokenArr_destroy(&test);
 * }
 */
