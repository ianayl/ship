/*
 * Whoops.
 * I'm an idiot.
 * This is a horrible way to start the shell.
 * I need to write a lexer first, and then a parser
 *
 * Guess I'll keep this for reference. This'll come
 * useful when I'm actually writing interactive stuff
 * I suppose.
 */
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

int is_interactive;
struct termios orig_state;

void init ()
{
        /* check if session is interactive */
        is_interactive = isatty(STDIN_FILENO);

        if (is_interactive) {
                /* save original state of terminal */
                tcgetattr(STDIN_FILENO, &orig_state);

                /* enable flags for no echo */
                struct termios raw_state = orig_state;
                raw_state.c_lflag &= ~(ECHO | ICANON);
                tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_state);
        }

}

void clean_exit ()
{
        if (is_interactive)
                tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_state);
}

char** parse_interactive ()
{
        /* status of the parser */
        int is_reading = 1;

        /* allocates memory for the input buffer */
        int bufsize = 1024;
        char* buffer = malloc(sizeof(char) * bufsize);
        if (!buffer) {
                fprintf(stderr,
                        "pish: Could not allocate memory for input buffer.\n");
                exit(-1);
        }

        /* read setup */
        char c;
        int pos = 0;

        /* print prompt once at the beginning */
        printf("%% ");

        /* actual parsing part TODO clean this up */
        while (is_reading) {
                c = fgetc(stdin);
                if (c == 127) { 
                        /* Backspace */
                        if (pos > 0) {
                                pos--;
                                buffer[pos] = 0;
                        }
                } else if (c == '\n') {
                        /* new line, return results */
                        printf("\n%s", buffer);
                        is_reading = 0;
                        continue;
                } else if (c == EOF ||
                           c == 4) 
                {
                        /* EOF apparently's 4, the variable no work */
                        is_reading = 0;
                        continue;
                } else {
                        buffer[pos] = c;
                        pos++;
                }

                if (pos >= bufsize) {
                        bufsize += 1024;
                        buffer = realloc(buffer, sizeof(char) * 1024);
                        /* ^ wrong */
                        if (!buffer) {
                                fprintf(stderr,
                                        "pish: Could not allocate memory for \
                                        input buffer.\n");
                                exit(-1);
                        }
                }

                printf("\r\033[2K%% %s\0337\t\t(char:%d pos%d)\0338", buffer, c, pos);
                fflush(stdout);
        };

}

void repl ()
{
        /* TODO implement reading from a file... that's kind of neccesary */
        char* command;
        parse_interactive(command);
        /* cleanup */
        free(command);
}

int main ()
{
        init();

        /* TODO read flags */
 
        /* TODO read rcs, profiles, etc */

        /* Main loop */
        repl();

        /* clean exit */
        clean_exit();
        exit(0);
}
