 //Jeremy McCormick
// CS 201 Assignment 1
// bst.c
#include <assert.h>
#include <math.h>
#include "queue.h"
#include "stack.h"

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
    free(n->value;)
    free(n->parent);
    free(n->left);
    free(n->right);
    free(n);
}

 
/////////////////////////////////
//          heap.c             //
/////////////////////////////////
    
QUEUE * queue;
STACK * buildStack;  //stack to keep track of inserted nodes for build heap operation

struct heap 
{
    BSTNODE * root;
    int size;
    void (*display)(void *,FILE *);
    int (*compare)(void *,void *);
    void (*free)(void *);
}
    
HEAP *newHEAP(
        void (*d)(void *,FILE *),    //display
        int (*c)(void *,void *),     //compare
        void (*f)(void *))          //free
{
    HEAP * heap = malloc(sizeof(HEAP));
    heap->root = NULL;
    heap->size = 0;
    heap->display = d;
    heap->compare = c;
    heap->free    = f;
    return heap;
}

void insertHEAP(HEAP *h,void *value)
{
    BSTNODE * newNode = newBSTNODE(value);
    buildStack = newSTACK(NULL, freeBSTNODE(BSTNODE *) );
    
    push(buildStack, newNode);
    
    if(h->size == 0)
    {
        h->root = newNode;
        h->size++;
        return;
    }
    
    
    // To find the open spot we get the binary representatin of the size
    // skip the msb, then the next digit we go right if 1 or left if 0. The LSB tells
    // us put as the right child if 1, left if 0
    int binaryLength = ceil(log(h->size));
    int size = h->size;
    BSTNODE * current = h->root
    for( int i = binaryLength; i >= 0; i--)
    {
            int bit = h & (2^i);
            if(i == binaryLength)
                continue;
            
            if(bit == 1)
            {
                current = getBSTNODEright(current);
                continue;
            }
            if(bit == 0)
            {
                current = getBSTNODEleft(current);
                continue;
            }
            
            if(bit == 1 && i == 0)
            {
                setBSTNODEright(current,newNode);
                setBSTNODEparent(newNode,current);
                return;
            }
            if(bit == 0 && i == 0)
            {
                setBSTNODEleft(current,newNode);
                setBSTNODEparent(newNode,current);
                return;
            }
    }
    
}
void buildHEAP(HEAP *h)
{
    while(sizeSTACK(buildStack) > 0)
    {
        heapify(h, pop(buildStack));
    }
}

void maxheapify(HEAP * heap, BSTNODE * n)
{
    BSTNODE * node = n;
    
    while(node != NULL)
    {
        if(heap->compare(getBSTNODE(node), getBSTNODEleft(node)) < 0 &&  heap->compare(getBSTNODEleft(node), getBSTNODEright(node)) > 0)
        {
                void * tmp = getBSTNODE(node)
                setBSTNODE(node, getBSTNODE( getBSTNODEleft(node)));
                setBSTNODE(getBSTNODEleft(node), getBSTNODE(tmp));
                node = getBSTNODEleft(node);
                continue;
        }
        if(heap->compare(getBSTNODE(node), getBSTNODEright(node)) < 0 &&  heap->compare(getBSTNODEleft(node), getBSTNODEright(node)) < 0)
        {
                void * tmp = getBSTNODE(node)
                setBSTNODE(node, getBSTNODE( getBSTNODEright(node)));
                setBSTNODE(getBSTNODEright(node), getBSTNODE(tmp));
                node = getBSTNODEright(node);
                continue;
        }
        else
            return;
}

void *peekHEAP(HEAP *h)
{
        return heap->root;
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
    
    heapify(h->root);
}

int  sizeHEAP(HEAP *h)
{
        return h->size;
}

void displayHEAP(HEAP *h,FILE *fp)
void displayHEAPdebug(HEAP *h)

void freeHEAP(HEAP *h)
{
    while(sizeSTACK(buildStack) > 0)
    {
        freeBSTNODE( pop(buildStack));
    }
    free(h->display)
    free(h->compare)
    free(h->free)
}
    
    
    
