 //Jeremy McCormick
// CS 201 Assignment 1
// bst.c
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include "queue.h"
#include "stack.h"
#include "heap.h"
//////////////////////////////
//          bstnode.c       //
//////////////////////////////

struct bstnode
{
    void * value;
    BSTNODE * parent;
    BSTNODE * left;
    BSTNODE * right;
};

BSTNODE *newBSTNODE(void *v)
{
    BSTNODE * node = malloc(sizeof(BSTNODE));
    assert(node != 0);
    node->value = v;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void    *getBSTNODE(BSTNODE *n)                          { return n->value; }
void    setBSTNODE(BSTNODE *n,void *value)               { n->value = value; }
BSTNODE *getBSTNODEleft(BSTNODE *n)                      { return n->left; }
void    setBSTNODEleft(BSTNODE *n,BSTNODE *replacement)  { n->left = replacement; }
BSTNODE *getBSTNODEright(BSTNODE *n)                     { return n->right; }
void    setBSTNODEright(BSTNODE *n,BSTNODE *replacement) { n->right = replacement; }
BSTNODE *getBSTNODEparent(BSTNODE *n)                    { return n->parent; }
void    setBSTNODEparent(BSTNODE *n,BSTNODE *replacement){ n->parent = replacement; }

void    freeBSTNODE(BSTNODE *n)
{
    free(n->value);
    free(n->parent);
    free(n->left);
    free(n->right);
    free(n);
}

 
/////////////////////////////////
//          heap.c             //
/////////////////////////////////
    
QUEUE * inQueue;
STACK * buildStack;  //stack to keep track of inserted nodes for build heap operation
void freebstnode(void *);
struct heap 
{
    BSTNODE * root;
    int size;
    void (*display)(void *,FILE *);
    int (*compare)(void *,void *);
    void (*free)(void *);
};
    
HEAP *newHEAP(void (*d)(void *,FILE *), int (*c)(void *,void *), void (*f)(void *))      
{
    HEAP * heap = malloc(sizeof(HEAP));
    heap->root = NULL;
    heap->size = 0;
    heap->display = d;
    heap->compare = c;
    heap->free    = f;
    return heap;
}
void freebstnode(void * in)
{
        freeBSTNODE((BSTNODE*)in);
}
void insertHEAP(HEAP *h,void *value)
{
    BSTNODE * newNode = newBSTNODE(value);
    buildStack = newSTACK(NULL, freebstnode );
    inQueue = newQUEUE(NULL, freebstnode );
    push(buildStack, newNode);
    enqueue(inQueue, newNode);
    
    if(h->size == 0)
    {
        h->root = newNode;
        h->size++;
        return;
    }
    
    BSTNODE * tmp = peekQUEUE(inQueue);
    
    if(getBSTNODEleft(tmp) == NULL)
    {
        setBSTNODEleft(tmp, newNode);
        setBSTNODEparent(newNode, tmp);
    }
    else if (getBSTNODEright(tmp) == NULL)
    {
        setBSTNODEright(tmp, newNode);
        setBSTNODEparent(newNode,tmp);
        dequeue(inQueue);
    }
    
}
void buildHEAP(HEAP *h)
{
    while(sizeSTACK(buildStack) > 0)
    {
        maxheapify(h, pop(buildStack));
    }
}

void maxheapify(HEAP * heap, BSTNODE * n)
{
    BSTNODE * node = n;
    
    while(node != NULL)
    {
        if(heap->compare(getBSTNODE(node), getBSTNODEleft(node)) < 0 &&  heap->compare(getBSTNODEleft(node), getBSTNODEright(node)) > 0)
        {
                void * tmp = getBSTNODE(node);
                setBSTNODE(node, getBSTNODE( getBSTNODEleft(node)));
                setBSTNODE(getBSTNODEleft(node), getBSTNODE(tmp));
                node = getBSTNODEleft(node);
                continue;
        }
        if(heap->compare(getBSTNODE(node), getBSTNODEright(node)) < 0 &&  heap->compare(getBSTNODEleft(node), getBSTNODEright(node)) < 0)
        {
                void * tmp = getBSTNODE(node);
                setBSTNODE(node, getBSTNODE( getBSTNODEright(node)));
                setBSTNODE(getBSTNODEright(node), getBSTNODE(tmp));
                node = getBSTNODEright(node);
                continue;
        }
        else
            return;
    }
}

void *peekHEAP(HEAP *h)
{
        return h->root;
}

void *extractHEAP(HEAP *h)
{
    BSTNODE * lastNode = pop(buildStack);
    void * ret = getBSTNODE(h->root);
    void * tmp = getBSTNODE(lastNode);
    
    setBSTNODE(h->root, tmp);
    
    if(lastNode == getBSTNODEleft(getBSTNODEparent(lastNode)))
    {
        setBSTNODEleft(getBSTNODEparent(lastNode) , NULL);
    }
    else
    {
        setBSTNODEright(getBSTNODEparent(lastNode) , NULL);
    }
    freeBSTNODE(lastNode);
    
    maxheapify(h,h->root);
	return ret;
}

int  sizeHEAP(HEAP *h)
{
        return h->size;
}

void displayHEAP(HEAP *h,FILE *fp)
{
    fprintf(fp,"%d",(int)getBSTNODE(h->root));
}
void displayHEAPdebug(HEAP *h,FILE *fp)
{
    fprintf(fp,"%d",(int)getBSTNODE(h->root));
}

void freeHEAP(HEAP *h)
{
    while(sizeSTACK(buildStack) > 0)
    {
        freeBSTNODE( pop(buildStack));
    }
    free(h->root);
}
    
    
    
