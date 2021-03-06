//Jeremy McCormick
// CS 201 Assignment 1
// bst.c
#include <assert.h>
#include "bst.h"
#include "queue.h"

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

//BST, uses the above bst Node code
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
    
}
    extern BSTNODE *deleteBST(BST *t,void *value);
    extern BSTNODE *swapToLeafBST(BST *t,BSTNODE *node);
    extern void    pruneLeafBST(BST *t,BSTNODE *leaf);
    extern int     sizeBST(BST *t);
    extern void    statisticsBST(BST *t,FILE *fp);
    extern void    displayBST(BST *t,FILE *fp);
    extern void    displayBSTdebug(BST *t,FILE *fp);
    extern void    freeBST(BST *t);
