/* TODO PUT GENERIC, REPEATING PATTERNS INTO FUNCTIONS */
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
		if (input[i] == '\0' ) {

			/* 
			 * TODO if quotation is not finished, find
			 * a way to indicate that in the returned 
			 * TokenArr.
			 */

			if (buf_len > 1) {
				/* assigning new token to a generic type */
				enum tk_type generic_type = TOKEN;
				ta_push(dest, buf, generic_type);
			}

			str_end = 1;
			break;

		/* newlines are its own tokens */
		} else if (input[i] == '\n') {

			/* 
			 * TODO if quotation is not finished, find
			 * a way to indicate that in the returned 
			 * TokenArr.
			 */

			enum tk_type temp_type = TOKEN;

			if (buf_len > 1) {
				/* assigning new token to a generic type */
				ta_push(dest, buf, temp_type);
			}

			/* push newline token */
			temp_type = NEWLINE;
			ta_push(dest, "\n", temp_type);

			str_end = 1;
			break;

		/* POSIX standard token recognition check 4 */
		/* TODO implement backslash, escaping, etc  */
		} else if (input[i] == '\"' || input[i] == '\'') {

			enum tk_type generic_type = TOKEN;

			if (in_quotes == input[i]) {

				buf_len ++;
				buf = realloc(buf, buf_len);
				buf[buf_len-1] = '\0';
				buf[buf_len-2] = input[i];

				/* 
				 * TODO figure out what type would quoted text
				 * fit under
				 */
				ta_push(dest, buf, generic_type);
				free(buf);
				buf = calloc(1, 1);
				buf_len = 1;

				in_quotes = 0;

			} else if (!in_quotes) {

				/*
				 * TODO figure out what type would quoted text
				 * fit under
				 */
				ta_push(dest, buf, generic_type);
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
			
			enum tk_type temp_type = TOKEN;

			if (buf_len > 1) {
				/* assigning new token to a generic type */
				ta_push(dest, buf, temp_type);

				free(buf);
				buf = calloc(1, 1);
				buf_len = 1;
			}


			/* &&, AND_IF */
			if (input[i+1] == '&') {
				/* TODO wait if this works I will be so mad */
				ta_push(dest, "&&", OP_ANDIF);
				i++;	

			/* &, AMPERSAND */
			/* 
			 * the name 'AMPERSAND' probably isn't convention, but 
			 * the only convention I could find for the name of '&'
			 * was literally just '&', and I can't have '&' as the 
			 * name of something in an enum, so 'AMPERSAND' will
			 * have to do.
			 */
			} else {
				temp_type = OP_AMPERSAND;
				ta_push(dest, "&", temp_type);
			}

		} else if (input[i] == '|') {

			enum tk_type temp_type = TOKEN;

			if (buf_len > 1) {
				/* assigning new token to a generic type */
				ta_push(dest, buf, temp_type);

				free(buf);
				buf = calloc(1, 1);
				buf_len = 1;
			}

			/* ||, AND_OR */
			if (input[i+1] == '|') {
				temp_type = OP_ANDOR;
				ta_push(dest, "||", temp_type);
				i++;	

			/* |, PIPE */
			/* 
			 * the name 'PIPE' probably isnt convention either, but
			 * same reason as 'AMPERSAND', there's not much I can 
			 * do franky... thank you POSIX standard, very cool.
			 */
			} else {
				temp_type = OP_PIPE;
				ta_push(dest, "|", temp_type);
			}

		} else if (input[i] == ';') {

			enum tk_type temp_type = TOKEN;

			if (buf_len > 1) {
				/* assigning new token to a generic type */
				ta_push(dest, buf, temp_type);

				free(buf);
				buf = calloc(1, 1);
				buf_len = 1;
			}

			/* ;;, DSEMI */
			if (input[i+1] == ';') {
				temp_type = OP_DSEMI;
				ta_push(dest, ";;", temp_type);
				i++;	

			/* ;, SEMICOLON */
			/*
			 * again... see above comments for the rationale of
			 * 'SEMICOLON' as the name...
			 */
			} else {
				temp_type = OP_SEMICOLON;
				ta_push(dest, ";", temp_type);
			}

		} else if (input[i] == '<') {

			enum tk_type temp_type = TOKEN;

			if (buf_len > 1) {
				/* assigning new token to a generic type */
				ta_push(dest, buf, temp_type);

				free(buf);
				buf = calloc(1, 1);
				buf_len = 1;
			}

			if (input[i+1] == '<') {
				
				/* <<-, DLESSDASH */
				if (input[i+2] == '-') {
					temp_type = OP_DLESSDASH;
					ta_push(dest, "<<-", temp_type);
					i = i+2;	

				/* <<, DLESS */
				} else {
					temp_type = OP_DLESS;
					ta_push(dest, "<<", temp_type);
					i++;	
				}

			/* <&, LESSAND */
			} else if (input[i+1] == '&') {
				temp_type = OP_LESSAND;
				ta_push(dest, "<&", temp_type);
				i++;	

			/* <>, LESSGREAT */
			} else if (input[i+1] == '>') {
				temp_type = OP_LESSGREAT;
				ta_push(dest, "<>", temp_type);
				i++;	

			/* <, LESS */
			/* 
			 * same rationale as above comments, i just hope this 
			 * name isnt confusing. 'LESSTHAN' is not better either
			 */
			} else {
				temp_type = OP_LESS;
				ta_push(dest, "<", temp_type);
			}

		} else if (input[i] == '<') {

			enum tk_type temp_type = TOKEN;

			if (buf_len > 1) {
				/* assigning new token to a generic type */
				ta_push(dest, buf, temp_type);

				free(buf);
				buf = calloc(1, 1);
				buf_len = 1;
			}

			/* >|, CLOBBER */ 
			if (input[i+1] == '|') {
				temp_type = OP_CLOBBER;
				ta_push(dest, ">|", temp_type);
				i++;	

			/* >>, DGREAT */ 
			} else if (input[i+1] == '>') {
				temp_type = OP_DGREAT;
				ta_push(dest, ">>", temp_type);
				i++;	

			/* >&, GREATAND */ 
			} else if (input[i+1] == '&') {
				temp_type = OP_GREATAND;
				ta_push(dest, ">&", temp_type);
				i++;	

			/* >, GREAT */ 
			/* see comments above */
			} else {
				temp_type = OP_GREAT;
				ta_push(dest, ">", temp_type);
			}

		/* POSIX standard token recognition check 7 */
		} else if (input[i] == ' ' ||
			   input[i] == '\t' ||
			   input[i] == '\n' ||
			   input[i] == '\v' ||
			   input[i] == '\f' ||
			   input[i] == '\r' ) {

			if (buf_len > 1) {
				enum tk_type generic_type = TOKEN;
				ta_push(dest, buf, generic_type);
				free(buf);
				buf = calloc(1, 1);
				buf_len = 1;
			}

		/* POSIX standard token recognition check 9 */
		} else if (input[i] == '#') {

			if (buf_len > 1) {
				enum tk_type generic_type = TOKEN;
				ta_push(dest, buf, generic_type);
			}
			/* 
			 * TODO fix this, this is actually wrong behavior.
			 * It should instead recognize the \n at the back 
			 */
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
