 // Jeremy McCormick
 // CS 201 Assignment 1
 //heapsort.c
 
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "scanner.h"
#include "heap.h"


static int processOptions(int,char **);
void Fatal(char *,...);
void printVersion();
void processInts(char *);
int intcomp(int , int);
void processReal(char *);
void processToken(char *);
void displayInt(void *);

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

    
    static int
processOptions(int argc, char **argv)
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
        printf ("File not created");
        return 1;
    }
    while (!feof(fp))
    {
        insertHEAP(heap, readInt(fp));
    }
    fixHEAP(heap);
    showHEAP();
}

int intcomp(int a, int b)
{
        return a-b;
}

void processReal(char * filename)
{
    FILE *fp;
    fp = fopen (filename,"r");
    if (fp == NULL) {
        printf ("File not created");
        return 1;
    }
    while (!feof(fp))
    {
        insertHEAP(heap, readInt(fp));
    }
    fixHEAP(heap);
    showHEAP();
}
void processToken(char * filename)
{
    FILE *fp;
    fp = fopen (filename,"r");
    if (fp == NULL) {
        printf ("File not created");
        return 1;
    }
    while (!feof(fp))
    {
        insertHEAP(heap, readInt(fp));
    }
    fixHEAP(heap);
    showHEAP();
}

void displayInt(void * in)
{
    fprintf("%d", in, stdout);
}
