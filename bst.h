//Jeremy McCormick
// CS 201 Assignment 1
// bst.h

#ifndef __BST_INCLUDED__
    #define __BST_INCLUDED__

    #include <stdio.h>
//BST Node protion, incuded here for privacy as BST will be the only thing using it
    typedef struct bstnode BSTNODE;

    extern BSTNODE *newBSTNODE(void *v);
    extern void    *getBSTNODE(BSTNODE *n);
    extern void    setBSTNODE(BSTNODE *n,void *value);
    extern BSTNODE *getBSTNODEleft(BSTNODE *n);
    extern void    setBSTNODEleft(BSTNODE *n,BSTNODE *replacement);
    extern BSTNODE *getBSTNODEright(BSTNODE *n);
    extern void    setBSTNODEright(BSTNODE *n,BSTNODE *replacement);
    extern BSTNODE *getBSTNODEparent(BSTNODE *n);
    extern void    setBSTNODEparent(BSTNODE *n,BSTNODE *replacement);
    extern void    freeBSTNODE(BSTNODE *n,void (*free)(void *));

//BST, uses the above bst Node code
    typedef struct bst BST;

    extern BST *newBST(
        void (*)(void *,FILE *),           //display
        int (*)(void *,void *),            //comparator
        void (*)(BSTNODE *,BSTNODE *),     //swapper
        void (*)(void *));                 //free
    extern BSTNODE *getBSTroot(BST *t);
    extern void    setBSTroot(BST *t,BSTNODE *replacement);
    extern void    setBSTsize(BST *t,int s);
    extern BSTNODE *insertBST(BST *t,void *value);
    extern BSTNODE *findBST(BST *t,void *value);
    extern BSTNODE *deleteBST(BST *t,void *value);
    extern BSTNODE *swapToLeafBST(BST *t,BSTNODE *node);
    extern void    pruneLeafBST(BST *t,BSTNODE *leaf);
    extern int     sizeBST(BST *t);
    extern void    statisticsBST(BST *t,FILE *fp);
    extern void    displayBST(BST *t,FILE *fp);
    extern void    displayBSTdebug(BST *t,FILE *fp);
    extern void    freeBST(BST *t);
    #endif
