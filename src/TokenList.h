#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TOKENLIST_H
#define TOKENLIST_H

typedef struct TKL_node {
        /* struct TKL_node *prev; */
        struct TKL_node *next;
        char* token;
} TKL_node;

typedef struct TokenList {
        TKL_node *head;
        TKL_node *tail;
        int len;
} TokenList;

TokenList TKL_newList ();

void TKL_append (TokenList *target, char* val);

/* recursive helper function for TKL_wipe() */
void TKL_wipe_helper (TKL_node *head);

void TKL_wipe (TokenList *target);

#endif
