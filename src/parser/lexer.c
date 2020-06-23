#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tokens.h"

/* 
 * Lexes a string into tokens and places them into a TokenArr
 */
void lexer (struct tk_arr *dest, char* input)
{
	unsigned short str_end = 0;
	char* buf = calloc(1, 1);
	unsigned buf_len = 1;

	/*
	 * in_quotes has values of either:
	 * - 0 for not in quotes
	 * - the ascii value of the type of quote the lexer is 
	 *   currently in
	 */
	unsigned short in_quotes = 0;

	/*
	 * checks left TODO:
	 * 2, 3, 4 (wip), 5, 6 (wip)
	 */
	for (unsigned i = 0; !str_end; i++) {
		printf("%c buf:%s\n", input[i], buf);

		/* POSIX standard token recognition check 1 */
		if (input[i] == '\0' ||
		    input[i] == '\n') {

			/* 
			 * TODO if quotation is not finished, find
			 * a way to indicate that in the returned 
			 * TokenArr.
			 */
			if (buf_len > 1)
				ta_push(dest, buf);
			str_end = 1;
			break;

		/* POSIX standard token recognition check 4 */
		/* TODO implement backslash, escaping, etc  */
		} else if (input[i] == '\"' || input[i] == '\'') {

			if (in_quotes == input[i]) {

				buf_len ++;
				buf = realloc(buf, buf_len);
				buf[buf_len-1] = '\0';
				buf[buf_len-2] = input[i];

				ta_push(dest, buf);
				free(buf);
				buf = calloc(1, 1);
				buf_len = 1;

				in_quotes = 0;

			} else if (!in_quotes) {

				ta_push(dest, buf);
				free(buf);

				buf = calloc(2, 1);
				buf[0] = input[i];
				buf_len = 2;

				in_quotes = input[i];
				
			} else {

				buf_len ++;
				buf = realloc(buf, buf_len);
				buf[buf_len-1] = '\0';
				buf[buf_len-2] = input[i];

			}

		} else if (in_quotes) {

			buf_len ++;
			buf = realloc(buf, buf_len);
			buf[buf_len-1] = '\0';
			buf[buf_len-2] = input[i];

		/* POSIX standard token recognition check 6 */
		/* TODO fill in each operator lol */
		} else if (input[i] == '&') {
			
			/* &&, AND_IF */
			if (input[i+1] == '&') {

			/* &, AMPERSAND */
			/* 
			 * the name 'AMPERSAND' probably isn't convention, but 
			 * the only convention I could find for the name of '&'
			 * was literally just '&', and I can't have '&' as the 
			 * name of something in an enum, so 'AMPERSAND' will
			 * have to do.
			 */
			} else {

			}

		} else if (input[i] == '|') {

			/* ||, AND_OR */
			if (input[i+1] == '|') {

			/* |, PIPE */
			/* 
			 * the name 'PIPE' probably isnt convention either, but
			 * same reason as 'AMPERSAND', there's not much I can 
			 * do franky... thank you POSIX standard, very cool.
			 */
			} else {

			}

		} else if (input[i] == ';') {

			/* ;;, DSEMI */
			if (input[i+1] == ';') {

			/* ;, SEMICOLON */
			/*
			 * again... see above comments for the rationale of
			 * 'SEMICOLON' as the name...
			 */
			} else {

			}

		} else if (input[i] == '<') {

			if (input[i+1] == '<') {
				
				/* <<-, DLESSDASH */
				if (input[i+2] == '-') {

				/* <<, DLESS */
				} else {

				}

			/* <&, LESSAND */
			} else if (input[i+1] == '&') {

			/* <>, LESSGREAT */
			} else if (input[i+1] == '>') {

			/* <, LESS */
			/* 
			 * same rationale as above comments, i just hope this 
			 * name isnt confusing. 'LESSTHAN' is not better either
			 */
			} else {

			}

		} else if (input[i] == '<') {

			/* >|, CLOBBER */ 
			if (input[i+1] == '|') {

			/* >>, DGREAT */ 
			} else if (input[i+1] == '>') {

			/* >&, GREATAND */ 
			} else if (input[i+1] == '&') {

			/* >, GREAT */ 
			/* see comments above */
			} else {

			}

		/* POSIX standard token recognition check 7 */
		} else if (input[i] == ' ' ||
			   input[i] == '\t' ||
			   input[i] == '\n' ||
			   input[i] == '\v' ||
			   input[i] == '\f' ||
			   input[i] == '\r' ) {

			if (buf_len > 1) {
				ta_push(dest, buf);
				free(buf);
				buf = calloc(1, 1);
				buf_len = 1;
			}

		/* POSIX standard token recognition check 9 */
		} else if (input[i] == '#') {

			if (buf_len > 1)
				ta_push(dest, buf);
			str_end = 1;
			break;
			
		/* POSIX standard token recognition check 8 */
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

	struct tk_arr tokens = ta_new();
	lexer(&tokens, argv[1]);
	for (int i = 0; i<tokens.len; i++) {
		printf("%s$\n", ta_get_val(&tokens, i));
	}
	ta_destroy(&tokens);
}
