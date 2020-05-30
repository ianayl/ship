#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tokens.h"

struct token_arr ta_new ()
{
	struct token_arr res;

	res.len = 0;
	res.queue = 0;

	return res;
}

void ta_push (struct token_arr *dest, char* v)
{
	/* TODO consider accomidating types*/
	if (dest->len == 0)
		dest->queue = malloc(sizeof(struct token));
	else
		dest->queue = realloc(dest->queue, (dest->len + 1)
					  * sizeof(struct token));
	/* assuming sizeof(char) = 0 */
	dest->queue[dest->len].val = malloc(strlen(v) + 1);
	strcpy(dest->queue[dest->len].val, v);

	dest->len ++;
}

char* ta_get_val (struct token_arr *dest, unsigned index)
{
	if (index >= dest->len || index < 0)
		return 0;
	return dest->queue[index].val;
};

void ta_destroy (struct token_arr *dest)
{
	for (int i = (dest->len - 1); i >= 0; i--)
		free(dest->queue[i].val);
	free(dest->queue);
}

/* 
 * just testing code, pls ignore lol
 *
 * int main ()
 * {
 *         struct token_arr test = ta_new();
 *         ta_push(&test, "abc");
 *         ta_push(&test, "def");
 *         ta_push(&test, "ghi");
 *         for (int i = 0; i<test.len; i++)
 *      	   printf("%s\n", ta_get_val(&test, i));
 *         ta_destroy(&test);
 * }
 */
