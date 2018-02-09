 //Jeremy McCormick
 //stack.c
 //CS 201 Assignment 0


#include <assert.h>
#include <stdlib.h>
#include "dll.h"
#include "stack.h"

struct stack{
    DLL * dll;
    void (*display)(void *, FILE *);
    void (*free)(void *);
};

STACK *newSTACK(void (*d)(void *,FILE *),void (*f)(void *))
{
    STACK * items = malloc(sizeof(STACK));
    items->dll= newDLL(d,f);
    items->display = d;
    items->free = f;
    return items;
}

void push(STACK *items,void *value)
{
    insertDLL(items->dll, 0, value); //insert new item to front of DLL
}

void *pop(STACK *items)
{
    return removeDLL(items->dll, 0); //remove from front of DLL and return
}

void *peekSTACK(STACK *items)
{
    return getDLL(items->dll,0);
}

int sizeSTACK(STACK *items)
{
        return sizeDLL(items->dll);
}

void displaySTACK(STACK *items,FILE * fp)
{
        printf("|");
        for(int i = 0; i < sizeDLL(items->dll) ; i++)
        {
            items->display(getDLL(items->dll, i), fp);
            if(i != sizeDLL(items->dll)-1)
                printf(",");
        }
        printf("|");
            
}

void displaySTACKdebug(STACK *items,FILE * fp)
{
        
        if(sizeDLL(items->dll) == 1)
        {
            printf("head->{");
            items->display(getDLL(items->dll, 0), fp);
            printf("},tail->{");
            items->display(getDLL(items->dll, 0), fp);
            printf("}");
            return;
        }
        printf("head->{");
        for(int i = 0; i < sizeDLL(items->dll) ; i++)
        {
            if(i == (sizeDLL(items->dll) - 1))
                printf("}, tail->{");
            items->display(getDLL(items->dll, i), fp);
            if(i < (sizeDLL(items->dll)-2))
                printf(",");
            
        }
        printf("}");
}

void freeSTACK(STACK *items)
{
        freeDLL(items->dll);
        free(items);
}

