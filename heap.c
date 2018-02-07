 //Jeremy McCormick
// CS 201 Assignment 1
// bst.c
#include <assert.h>
#include <math.h>
#include "bst.h"
#include "queue.h"


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

void    freeBSTNODE(BSTNODE *n,void (*free)(void *))
{
    free(n->value;)
    free(n->parent);
    free(n->left);
    free(n->right);
    free(n);
}

//////////////////////////////
//          bst.c           //
//////////////////////////////

struct bst
{
    BSTNODE * root;
    int size;
    void (*display)(void *,FILE *);
    int (*compare)(void *,void *);
    void (*swapper)(BSTNODE *,BSTNODE *);
    void (*free)(void *);
};

BST *newBST(
        void (*display)(void *,FILE *),           //display
        int (*compare)(void *,void *),            //comparator
        void (*swapper)(BSTNODE *,BSTNODE *),     //swapper
        void (*free)(void *))              //free
{
        BST * bst = malloc(sizeof(BST));
        bst->display = display;
        bst->compare = compare;
        bst->swapper = swapper;
        bst->free = free;
}

BSTNODE *getBSTroot(BST *t)
{
        return t->root;
}

void    setBSTroot(BST *t,BSTNODE *replacement)
{
        t->root = replacement;
}

void    setBSTsize(BST *t,int s)
{
        t->size = s;
}

BSTNODE *insertBST(BST *t,void *value)
{
    BSTNODE * newNode = newBSTNODE(value);
    if(t->size == 0)
    {
        t->root = newNode;
        t->size += 1;
        return newNode;
    }
    
    return insertBSTrecurse(t->root, newNode);
    
}

BSTNODE *insertBSTrecurse(BSTNODE *t,BSTNODE *newNode)
{
        if(t->compare(t->value, newNode->value) >= 0 && getBSTNODEright(t) != NULL)
        {
                insertBSTrecurse(getBSTNODEright(t), newNode);
        }
        
        if(t->compare(t->value, newNode->value) < 0 && getBSTNODEleft(t) != NULL)
        {
                insertBSTrecurse(getBSTNODEleft(t), newNode);
        }
        
        if(t->compare(t->value, newNode->value) >= 0 && getBSTNODEright(t) == NULL)
        {
                setBSTNODEright(t,newNode);
                setBSTNODEparent(newNode, t);
        }
        if(t->compare(t->value, newNode->value) < 0 && getBSTNODEleft(t) == NULL)
        {
                setBSTNODEleft(t,newNode);
                setBSTNODEparent(newNode, t);
        }
        return newNode;
}

BSTNODE *findBST(BST *t,void *value)
{
    return findBSTrecurse(t->root,t,value);
}

BSTNODE *findBSTrecurse(BSTNODE *node, BST *t, void *value)
{
    if(getBSTNODEleft(node) == NULL && getBSTNODEright(node) == NULL)
        return NULL;
    
    if(t->compare(getBSTNODE(node), value) == 0)
        return node;
    
    if(t->compare(getBSTNODE(node), value) >= 0)
        return findBSTrecurse(getBSTNODEright(node),t,value);
    
    if(t->compare(getBSTNODE(node), value) < 0)
        return findBSTrecurse(getBSTNODEleft(node),t,value); 
}
    
BSTNODE *deleteBST(BST *t,void *value)
{
}
    extern BSTNODE *swapToLeafBST(BST *t,BSTNODE *node);
    extern void    pruneLeafBST(BST *t,BSTNODE *leaf);
    extern int     sizeBST(BST *t);
    extern void    statisticsBST(BST *t,FILE *fp);
    extern void    displayBST(BST *t,FILE *fp);
    extern void    displayBSTdebug(BST *t,FILE *fp);
    extern void    freeBST(BST *t);

 
 
 
/////////////////////////////////
//          heap.c             //
/////////////////////////////////
    
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
            if(bit == 1 && i == 0)
            {
                setBSTNODEleft(current,newNode);
                setBSTNODEparent(newNode,current);
                return;
            }
    }
    
}
    extern void buildHEAP(HEAP *h);

void *peekHEAP(HEAP *h)
{
        return h->bst
}
    extern void *extractHEAP(HEAP *h);
    extern int  sizeHEAP(HEAP *h);
    extern void displayHEAP(HEAP *h,FILE *fp);
    extern void displayHEAPdebug(HEAP *h);
    extern void freeHEAP(HEAP *h);
    
    
    
