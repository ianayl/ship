#include "TokenList.h"

TokenList TKL_newList () 
{
        TokenList res;

        res.head = 0;
        res.tail = 0;
        res.len = 0;

        return res;
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

/* Do I even use this at all? Consider deleting this */
TKL_node* TKL_get (TokenList *target, int index)
{
        TKL_node *res = target->head;
        for (int i = 0; i < index; i++)
                res = res->next;
        return res;
}

/* For debug only, delete when done */
int main ()
{
        TokenList lol = TKL_newList();

        TKL_append(&lol, "hello");
        TKL_append(&lol, "nope");
        TKL_append(&lol, "bye");

        printf("%s\n", lol.head->token);
        printf("%s\n", lol.tail->token);
        printf("%d\n", lol.len);

        TKL_node *current = TKL_get(&lol, 1);

        printf("%s\n", current->token);

        TKL_wipe(&lol);
}
