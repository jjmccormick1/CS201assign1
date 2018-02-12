 
//Jeremy McCormick
// CS 201 Assignment 1
// heap.h


    #include <stdio.h>
//BST Node protion, incuded here for privacy as BST will be the only thing using it
    //////////////////////////////
    //          bstnode.h           //
    //////////////////////////////
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
    extern void    freeBSTNODE(BSTNODE *n);

    //////////////////////////////
    //          bst.h           //
    //////////////////////////////
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


    ///////////////////////////////
    //  Heap.h                   //
    ///////////////////////////////
    
    #ifndef __HEAP_INCLUDED__
    #define __HEAP_INCLUDED__

    #include <stdio.h>

    typedef struct heap HEAP;

    extern HEAP *newHEAP(
        void (*)(void *,FILE *),    //display
        int (*)(void *,void *),     //compare
        void (*)(void *));          //free
    extern void insertHEAP(HEAP *h,void *value);
    extern void buildHEAP(HEAP *h);
    extern void maxheapify(HEAP * heap, BSTNODE * n);
    extern void *peekHEAP(HEAP *h);
    extern void *extractHEAP(HEAP *h);
    extern int  sizeHEAP(HEAP *h);
    extern void displayHEAP(HEAP *h,FILE *fp);
    extern void displayHEAPdebug(HEAP *h);
    extern void freeHEAP(HEAP *h);
    #endif
