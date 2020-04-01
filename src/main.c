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

void parse_input ()
{
        /* allocates memory for the input buffer */
        int bufsize = 1024;
        char *buffer = malloc(sizeof(char) * bufsize);
        if (!buffer) {
                fprintf(stderr,
                        "pish: Could not allocate memory for input buffer.\n");
                exit(-1);
        }

        /* reads 1 char and adds to buffer */
        char c;
        int pos = 0;
        int status = 1;

        while (status) {
                c = fgetc(stdin);
                if (c == 127) { /* Backspace */
                        if (pos > 0) {
                                pos--;
                                buffer[pos] = 0;
                        }
                } else if (c == EOF ||
                    c == '\n' ||
                    c == 4) /* EOF apparently, the variable no work */
                {
                        status = 0;
                        continue;
                } else {
                        buffer[pos] = c;
                        pos++;
                }

                if (pos >= bufsize) {
                        bufsize += 1024;
                        buffer = realloc(buffer, bufsize);
                        if (!buffer) {
                                fprintf(stderr,
                                        "pish: Could not allocate memory for \
                                        input buffer.\n");
                                exit(-1);
                        }
                }

                printf("%s\t\t\tchar:%d pos:%d\n", buffer, c, pos);
        };
}

void repl ()
{
        parse_input();
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
