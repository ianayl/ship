#ifndef TOKENS_H
#define TOKENS_H

/* Stores a single token and it's type */
struct token
{
	char* val;
	/* TODO add type enum */

} token;

/* A queue of tokens */
struct token_arr
{
	struct token* queue;
	unsigned len;
} token_arr;

struct token_arr ta_new ();

void ta_push (struct token_arr *dest, char* v);

char* ta_get_val (struct token_arr *dest, unsigned index);

void ta_destroy (struct token_arr *dest);

#endif
