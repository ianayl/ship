#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tokens.h"

/* Helper function for lexer() to reset the dest. buffer */
void buf_clear (char** dest, unsigned *dest_len)
{
	free(*dest);
	*dest = calloc(1, 1);
	*dest_len = 1;
}

/* Helper function for lexer() to append a char onto the dest. buffer */
void buf_append_char (char** dest, unsigned *dest_len, char src)
{
	/* 
	 * I don't think expanding size by 1
	 * everytime is the best approach perf tho,
	 * might want to optimize this 
	 */
	*dest_len = *dest_len + 1;
	char* tmp = realloc(*dest, *dest_len);
	tmp[*dest_len-1] = '\0';
	tmp[*dest_len-2] = src;
	*dest = tmp;
}

/* Lexes a string into tokens and places them into a tk_arr */
void lexer (struct tk_arr *dest, char* input)
{
	unsigned short str_end = 0;
	char* buf = calloc(1, 1);
	unsigned buf_len = 1;

	/* 
	 * Is the lexer currently in quotes? 
	 * See parser/tokens.h
	 */
	unsigned short in_quotes = 0;

	/* Is the lexer currently in a comment? */
	unsigned short in_comment = 0;
	
	/* Is the lexer currently escaping a character? */
	unsigned short in_escape = 0;

	/*
	 * Is the lexer currently in command substitution? 
	 * See parser/tokens.h
	 */
	unsigned short in_sub_cmd = 0;

	/* Is the lexer currently in arithmetic expansion? */
	unsigned short in_exp_arith = 0;

	/* Is the lexer currently in parameter expansion? */
	unsigned short in_exp_param = 0;

	/* The level of nesting the current substitution / expansion */
	int nest_lvl = 0;

	/*
	 * Checks left TODO:
	 * 5
	 */
	for (unsigned i = 0; !str_end; i++) {
		/* DEBUG */
		printf("%c buf:%s esc:%d quo:%d com:%d\n",
		       input[i],
		       buf,
		       in_escape,
		       in_quotes,
		       in_comment);

		/* POSIX standard token recognition check 1 */
		if (input[i] == '\0' ) {

			if (buf_len > 1)
				ta_push(dest, buf, TOKEN);
			str_end = 1;
			break;

		/* If current character is to be escaped */
		} else if (in_escape) {

			if (in_quotes == '\'')
				/* Don't care */
				buf_append_char(&buf, &buf_len, '\\');

			else if (in_quotes == '\"') {
				/* 
				 * Section 2.2.1, escaped newlines mean line cont.
				 *
				 * However, only do it for newlines at the end of the
				 * input, or else in_line_cont would be true even if
				 * it didn't need to be true
				 */
				if (input[i] == '\n' && input[i+1] == '\0')
					dest->in_line_cont = 1;

				else if (input[i] == '$' ||
					 input[i] == '`' ||
					 input[i] == '\"' ||
					 input[i] == '\\')
				{
					/* Escape needed for only these characters */
					buf_append_char(&buf, &buf_len, input[i]);

				} else {
					/* Adding the backslash back lol */
					buf_append_char(&buf, &buf_len, '\\');
					buf_append_char(&buf, &buf_len, input[i]);
				}

			} else {
				/* Section 2.2.1, escaped newlines mean line cont. */
				if (input[i] == '\n' && input[i+1] == '\0')
					dest->in_line_cont = 1;
				else
					buf_append_char(&buf, &buf_len, input[i]);
			}
			in_escape = 0;

		/* Escape next character */
		} else if (input[i] == '\\')
			in_escape = 1;

		/* Newlines are its own tokens */
		else if (input[i] == '\n') {

			if (buf_len > 1) {
				ta_push(dest, buf, TOKEN);
				buf_clear(&buf, &buf_len);
			}
			ta_push(dest, "\n", NEWLINE);

		} else if (in_comment) {

			/*
			 * It's a comment, do nothing. 
			 * The rest of the rules do not apply
			 */

		/* POSIX standard token recognition check 4 */
		} else if (input[i] == '\"' || input[i] == '\'') {

			if (in_quotes == input[i]) {

				buf_append_char(&buf, &buf_len, input[i]);
				/* 
				 * TODO figure out what type would quoted text
				 * fit under
				 */
				ta_push(dest, buf, TOKEN);
				buf_clear(&buf, &buf_len);

				in_quotes = 0;

			/* If quotation mark is not nested in anything */
			} else if (!in_quotes &&
				   !in_sub_cmd)
			{
				if (buf_len > 1) {
					ta_push(dest, buf, TOKEN);
					buf_clear(&buf, &buf_len);
				}

				buf_append_char(&buf, &buf_len, input[i]);
				in_quotes = input[i];
				
			} else
				buf_append_char(&buf, &buf_len, input[i]);

		/* Don't check for operators or anything when in quotes */
		} else if (in_quotes)
			buf_append_char(&buf, &buf_len, input[i]);

		// /*
		//  * POSIX standard token recognition check 5 */
		//  * 
		//  * TODO checklist:
		//  * - Be able to process commands first
		//  *   - Be able to parse individual components, eg exp_arith
		//  *     or quotes or sub_cmd
		//  *   - AST the results (DO THIS FIRST)
		//  *   - The new AST tree is then processed
		//  *   - Return results
		//  * 
		//  * It would probably be a wise idea to:
		//  * - Develop arithmetic expansion first (DO THIS FIRST)
		//  *   - Make a separate function that takes text
		//  *   - Text is then lexed separately
		//  *     - Stuff like exp_arith and exp_param nested in the
		//  *       initial exp_arith should be handled here (do this
		//  *       later though)
		//  *   - Results are then put in it's own AST
		//  *   - AST'd results are processed
		//  *   - Return results
		//  * - Then handle parameter expansion
		//  * - And then follow up by handling subshells. If you are 
		//  *   able to get this far then you have some semblance of
		//  *   a shell, just implement stuff like:
		//  *    - Conditional structures
		//  *    - Redirection
		//  *    - Exit status
		//  *    - Heredocs
		//  *    - Builtins
		//  */
		// else if (input[i] == '`') {

		// 	if (in_sub_cmd == '`') {
		// 		/* Old command substitution */
		// 		buf_append_char(&buf, &buf_len, input[i]);
		// 		ta_push(dest, buf, SUB_CMD);
		// 		buf_clear(&buf, &buf_len);

		// 		in_sub_cmd = 0;

		// 	} else {
		// 		/* New command substitution */
		// 		if (buf_len > 1) {
		// 			ta_push(dest, buf, TOKEN);
		// 			buf_clear(&buf, &buf_len);
		// 		}

		// 		buf_append_char(&buf, &buf_len, input[i]);
		// 		in_sub_cmd = '`';
		// 	}

		// } else if (in_sub_cmd) {

		// 	buf_append_char(&buf, &buf_len, input[i]);

		// 	if (input[i] == ')') {
		// 	}


		// } else if (input[i] == '$') {

		// 	if (buf_len > 1) {
		// 		ta_push(dest, buf, TOKEN);
		// 		buf_clear(&buf, &buf_len);
		// 	}

		// 	if (input[i+1] == '(') {

		// 		if (input[i+2] == '(') {
		// 			/* Arithmetic Expansion */
		// 			buf_append_char(&buf,
		// 					&buf_len,
		// 					input[i]);
		// 			in_exp_arith = 1;

		// 		} else {
		// 			/* Command Substitution */
		// 			buf_append_char(&buf,
		// 					&buf_len,
		// 					input[i]);
		// 			in_sub_cmd = '$';
		// 		}

		// 	} else if (input[i+1] == '{') {
		// 		/* Parameter Expansion */
		// 		buf_append_char(&buf, &buf_len, '{');
		// 		in_exp_param = '{';

		// 	} else if (!in_sub_cmd &&
		// 		   !in_exp_arith &&
		// 		   !in_exp_param)
		// 	{
		// 		/* Still Parameter Expansion... but no {} */
		// 		buf_append_char(&buf, &buf_len, input[i]);
		// 		in_exp_param = '$';

		// 	} else
		// 		/* No new tokens, just append onto current token */
		// 		buf_append_char(&buf, &buf_len, input[i]);

		/* POSIX standard token recognition check 6 */
		// } else if (input[i] == '&') {
		else if (input[i] == '&') {
			
			if (buf_len > 1) {
				ta_push(dest, buf, TOKEN);
				buf_clear(&buf, &buf_len);
			}

			/* &&, AND_IF */
			if (input[i+1] == '&') {
				ta_push(dest, "&&", OP_ANDIF);
				i++;	

			/* &, AMPERSAND */
			/* 
			 * The name 'AMPERSAND' probably isn't convention, but 
			 * the only convention I could find for the name of '&'
			 * was literally just '&', and I can't have '&' as the 
			 * name of something in an enum, so 'AMPERSAND' will
			 * have to do.
			 */
			} else
				ta_push(dest, "&", OP_AMPERSAND);

		} else if (input[i] == '|') {

			if (buf_len > 1) {
				ta_push(dest, buf, TOKEN);
				buf_clear(&buf, &buf_len);
			}

			/* ||, AND_OR */
			if (input[i+1] == '|') {
				ta_push(dest, "||", OP_ANDOR);
				i++;	

			/* |, PIPE */
			/* 
			 * The name 'PIPE' probably isnt convention either, but
			 * same reason as 'AMPERSAND', there's not much I can 
			 * do franky... thank you POSIX standard, very cool.
			 */
			} else
				ta_push(dest, "|", OP_PIPE);

		} else if (input[i] == ';') {

			if (buf_len > 1) {
				ta_push(dest, buf, TOKEN);
				buf_clear(&buf, &buf_len);
			}

			/* ;;, DSEMI */
			if (input[i+1] == ';') {
				ta_push(dest, ";;", OP_DSEMI);
				i++;	

			/* ;, SEMICOLON */
			/* See above for rationale behind 'SEMICOLON' */
			} else
				ta_push(dest, ";", OP_SEMICOLON);

		} else if (input[i] == '<') {

			if (buf_len > 1) {
				ta_push(dest, buf, TOKEN);
				buf_clear(&buf, &buf_len);
			}

			if (input[i+1] == '<') {
				
				/* <<-, DLESSDASH */
				if (input[i+2] == '-') {
					ta_push(dest, "<<-", OP_DLESSDASH);
					i = i+2;	

				/* <<, DLESS */
				} else {
					ta_push(dest, "<<", OP_DLESS);
					i++;	
				}

			/* <&, LESSAND */
			} else if (input[i+1] == '&') {
				ta_push(dest, "<&", OP_LESSAND);
				i++;	

			/* <>, LESSGREAT */
			} else if (input[i+1] == '>') {
				ta_push(dest, "<>", OP_LESSGREAT);
				i++;	

			/* <, LESS */
			/* 
			 * Same rationale as above comments, i just hope this 
			 * name isnt confusing. 'LESSTHAN' is not better either
			 */
			} else
				ta_push(dest, "<", OP_LESS);

		} else if (input[i] == '>') {

			if (buf_len > 1) {
				ta_push(dest, buf, TOKEN);
				buf_clear(&buf, &buf_len);
			}

			/* >|, CLOBBER */ 
			if (input[i+1] == '|') {
				ta_push(dest, ">|", OP_CLOBBER);
				i++;	

			/* >>, DGREAT */ 
			} else if (input[i+1] == '>') {
				ta_push(dest, ">>", OP_DGREAT);
				i++;	

			/* >&, GREATAND */ 
			} else if (input[i+1] == '&') {
				ta_push(dest, ">&", OP_GREATAND);
				i++;	

			/* >, GREAT */ 
			/* See above for rationale behind 'GREAT' */
			} else
				ta_push(dest, ">", OP_GREAT);

		/* POSIX standard token recognition check 7 */
		} else if (input[i] == ' ' ||
			   input[i] == '\t' ||
			   input[i] == '\n' ||
			   input[i] == '\v' ||
			   input[i] == '\f' ||
			   input[i] == '\r' )
		{
			if (buf_len > 1) {
				ta_push(dest, buf, TOKEN);
				buf_clear(&buf, &buf_len);
			}

		/* POSIX standard token recognition check 9 */
		} else if (input[i] == '#') {
			if (buf_len > 1)
				ta_push(dest, buf, TOKEN);
			in_comment = 1;
			
		/* POSIX standard token recognition check 8 */
		} else
			buf_append_char(&buf, &buf_len, input[i]);
	}

	free(buf);
	/* syncing status of lexer with tk_arr */
	dest->in_quotes = in_quotes;
	dest->in_sub_cmd = in_sub_cmd;
	dest->in_exp_arith = in_exp_arith;
	dest->in_exp_param = in_exp_param;
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
		printf("%s$ - %d\n", ta_get_val(&tokens, i), ta_get_type(&tokens, i));
	}
	printf("in_quotes: %d\n", tokens.in_quotes);
	printf("in_line_cont: %d\n", tokens.in_line_cont);
	ta_destroy(&tokens);
}
