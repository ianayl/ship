#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tokens.h"

struct tk_arr ta_new ()
{
	struct tk_arr res;

	res.len = 0;
	res.arr = 0;

	return res;
}

void ta_push (struct tk_arr *dest, char* v) /* , enum tk_type t) */
{
	if (dest->len == 0)
		dest->arr = malloc(sizeof(struct token));
	else
		dest->arr = realloc(dest->arr, (dest->len + 1)
					  * sizeof(struct token));
	
	/* assuming sizeof(char) = 1 */
	dest->arr[dest->len].val = malloc(strlen(v) + 1);
	strcpy(dest->arr[dest->len].val, v);
	/* TODO add types */
	/* dest->arr[dest->len].type = t; */

	dest->len ++;
}

char* ta_get_val (struct tk_arr *dest, unsigned index)
{
	if (index >= dest->len || index < 0)
		return 0;
	return dest->arr[index].val;
};

void ta_destroy (struct tk_arr *dest)
{
	for (int i = (dest->len - 1); i >= 0; i--)
		free(dest->arr[i].val);
	free(dest->arr);
}

/* 
 * just testing code, pls ignore lol
 *
 * int main ()
 * {
 *         struct tk_arr test = ta_new();
 *         ta_push(&test, "abc");
 *         ta_push(&test, "def");
 *         ta_push(&test, "ghi");
 *         for (int i = 0; i<test.len; i++)
 *      	   printf("%s\n", ta_get_val(&test, i));
 *         ta_destroy(&test);
 * }
 */
