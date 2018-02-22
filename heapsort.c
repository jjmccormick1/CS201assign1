 // Jeremy McCormick
 // CS 201 Assignment 1
 //heapsort.c
 
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "scanner.h"
#include "heap.h"


static int processOptions(int,char **);
void Fatal(char *,...);
void printVersion();
void processInts(char *);
int intcomp(void * , void *);
void displayInt(void *, FILE *);
void processReal(char *);
int realcomp(void *, void *);
void displayReal(void *, FILE *);
void processToken(char *);
int tokencomp(void *, void *);
void displayToken(void *, FILE *);

//globals
int increasing = 0; //0 = dec, 1 = inc


int main(int argc,char **argv)
{
    //int argIndex;

    if (argc == 1) Fatal("%d arguments!\n",argc-1);

    processOptions(argc,argv);
    
    return 0;
}

void
Fatal(char *fmt, ...)
{
    va_list ap;

    fprintf(stderr,"An error occured: ");
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);

    exit(-1);
}

    
static int processOptions(int argc, char **argv)
{
    int argIndex;
    int argUsed;
    int separateArg;
    char *arg;

    argIndex = 1;

    while (argIndex < argc && *argv[argIndex] == '-')
        {
        /* check if stdin, represented by "-" is an argument */
        /* if so, the end of options has been reached */
        if (argv[argIndex][1] == '\0') return argIndex;

        separateArg = 0;
        argUsed = 0;

        if (argv[argIndex][2] == '\0')
            {
            arg = argv[argIndex+1];
            separateArg = 1;
            }
        else
            arg = argv[argIndex]+2;

        switch (argv[argIndex][1])
            {
            /*
             * when option has an argument, do this
             *
             *     examples are -m4096 or -m 4096
             *
             *     case 'm':
             *         MemorySize = atol(arg);
             *         argUsed = 1;
             *         break;
             *
             *
             * when option does not have an argument, do this
             *
             *     example is -a
             *
             *     case 'a':
             *         PrintActions = 1;
             *         break;
             */

            case 'v':
                printVersion();
                break;
            case 'i':
                processInts(arg);
                argUsed = 1;
                break;
            case 'r':
                processReal(arg);
                argUsed = 1;
                break;
            case 's':
                processToken(arg);
                argUsed = 1;
                break;
            case 'I':
                increasing = 1;
                break;
            case 'D':
                increasing = 0;
                break;
            default:
                Fatal("option %s not understood\n",argv[argIndex]);
            }

        if (separateArg && argUsed)
            ++argIndex;

        ++argIndex;
        }

    return argIndex;
}

void printVersion()
{
        printf("Jeremy McCormick \n Further Expanation...");
        
}

void processInts(char * filename)
{
    HEAP * heap = newHEAP(displayInt, intcomp, free);
    FILE *fp;
    fp = fopen (filename,"r");
    if (fp == NULL) {
        printf("File not created");
        return;
    }
    while (!feof(fp))
    {
        int read = readInt(fp);
        insertHEAP(heap, &read);
    }
    buildHEAP(heap);
    
    while(sizeHEAP(heap) != 0)
    {
            void * out = extractHEAP(heap);
            displayInt(out,stdout);
    }
}

int intcomp(void * a, void * b)
{
        return ((int*)a)  - ((int*)b);
}

void displayInt(void * in, FILE * fp)
{
    int *ptmp = (int*)in;
    int tmp = *ptmp;
    fprintf(fp,"%d", tmp);
}


void processReal(char * filename)
{
    HEAP * heap = newHEAP(displayReal, realcomp, free);
    FILE *fp;
    fp = fopen (filename,"r");
    if (fp == NULL) {
        printf ("File not created");
        return;
    }
    while (!feof(fp))
    {
        char * read = readString(fp);
        insertHEAP(heap, (void *)read);
    }
    buildHEAP(heap);
    
    while(sizeHEAP(heap) != 0)
    {
            void * out = extractHEAP(heap);
            displayReal(out,stdout);
    }
}
int realcomp(void * a, void * b)
{
    return ((float*)a) - ((float*)b);
}

void displayReal(void * in, FILE * fp)
{
    double *tmp = (double*)in;
    double dub = *tmp;
    fprintf(fp, "%f", dub);   
}
void processToken(char * filename)
{
    HEAP * heap = newHEAP(displayReal, realcomp, free);
    FILE *fp;
    fp = fopen (filename,"r");
    if (fp == NULL) {
        printf ("File not created");
        return;
    }
    while (!feof(fp))
    {
        insertHEAP(heap, readToken(fp));
    }
    buildHEAP(heap);
    
    while(sizeHEAP(heap) != 0)
    {
            void * out = extractHEAP(heap);
            displayToken(out,stdout);
    }
}

int tokencomp(void * a, void * b)
{
        return strcmp((char*)a,(char *)b);
}

void displayToken(void * in, FILE * fp)
{
    char * string = (char *)in;
    fprintf(fp, "%s", string);   
}
