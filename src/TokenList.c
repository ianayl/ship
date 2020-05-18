#include "TokenList.h"

TokenList TKL_newList () 
{
        TokenList tmp;

        tmp.head = 0;
        tmp.tail = 0;
        tmp.len = 0;

        return tmp;
}

void TKL_append (TokenList *target, char* val) 
{
        TKL_node *tmp = (TKL_node *) malloc(sizeof(TKL_node));

        tmp->next = 0;
        tmp->token = (char *) malloc(strlen(val)+1);
        strcpy(tmp->token, val);

        if (target->len == 0) {
                /* tmp->prev = 0; */
                target->head = tmp;
                target->tail = tmp;
        } else {
                /* tmp->prev = target->tail; */
                target->tail->next = tmp;
                target->tail = target->tail->next;
        }

        target->len ++;
}

/* recursive helper function for TKL_wipe() */
void TKL_wipe_helper (TKL_node *head)
{
        if (head->next != 0)
                TKL_wipe_helper(head->next);
        free(head->token);
        free(head);
}

void TKL_wipe (TokenList *target)
{
        TKL_wipe_helper(target->head);
        target->len = 0;
}

/*
 * for testing purposes only 
 * TODO delete when done
 */
int main ()
{
        TokenList lol = TKL_newList();

        TKL_append(&lol, "hello");
        TKL_append(&lol, "nope");
        TKL_append(&lol, "bye");

        printf("%s\n", lol.head->token);
        printf("%s\n", lol.tail->token);
        printf("%d\n", lol.len);

        TKL_wipe(&lol);
}
