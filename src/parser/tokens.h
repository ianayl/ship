#ifndef TOKENS_H
#define TOKENS_H

/* Types for tokens */
/* TODO document crap better */
enum tk_type
{

    /* Operators */
    OP_ANDIF, /* &&, AND logic */
    OP_AMPERSAND, /* &, asynchronous execution */
    OP_ANDOR, /* ||, OR logic */
    OP_PIPE, /* |, and uh... it's a pipe, idk what else to tell you */
    OP_DSEMI, /* ;;, I think it's only for case conditional constructs */
    OP_SEMICOLON, /* ;, do something, wait til its done, do next thing */
    OP_DLESSDASH, /* <<- */
    OP_DLESS, /* << */
    OP_LESSAND, /* <& */
    OP_LESSGREAT, /* <> */
    OP_LESS, /* < */
    OP_CLOBBER, /* >| */
    OP_DGREAT, /* >> */
    OP_GREATAND, /* >& */
    OP_GREAT /* > */

} tk_type;

/* Stores a single token and it's type */
struct token
{
	char* val;
    enum tk_type type;

} token;

/* An array of... well... tokens */
struct tk_arr
{
	struct token* arr;
	unsigned len;

} tk_arr;

struct tk_arr ta_new ();

void ta_push (struct tk_arr *dest, char* v);

char* ta_get_val (struct tk_arr *dest, unsigned index);

void ta_destroy (struct tk_arr *dest);

#endif
