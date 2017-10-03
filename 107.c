#! /usr/bin/tcc -run

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

    size_t linecap;
    FILE *fp;

typedef struct slot
{
    ssize_t size;
    char *row;
    int count;
}   slot;

    slot line;
    slot *text;

void etxt(int maxndx)
{
    printf("\n");

    int i;
    for (i = 0; i < maxndx + 1; i++)
    printf("the string at text[%d].row:  %.*s",
    i,text[i].size, text[i].row); 

    printf("\n"); 
    return;
}

// replaceAline should have one call to malloc and one call to free
// plus a free(text[nsrt].row 

void replaceAline(int nsrt,int maxndx)
{
    printf("the start value of <text> pointer is %p\n", (void *)text);

    slot *new  = (slot *)malloc(20*sizeof(slot));

    slot newline;
    char *ptr = "Hello World!\n";
    newline.size = strlen(ptr);
    char *qtr = (char *)malloc(strlen(ptr));
    memcpy(qtr,ptr,strlen(ptr)); 
    newline.row = qtr;

    slot *old = text; 

    int i,j,k; i = 0; j = 0; k = 0;
    for (i = 0 ; i < maxndx + 1 ; i++) 
      {if (i != nsrt) {new[j] = old[k]; j++; k++;}
       else           {new[j] = newline;j++; k++;}
      }

    free(text[nsrt].row);
    free(text); text = new;  
    printf("the end   value of <text> pointer is %p\n", (void *)text);

    return;
}

int readAline(void)
{
    line.row = NULL; linecap = 0;
    line.size = getline (&line.row, &linecap, fp); 

    if (line.size == -1) {return line.size;}

    if((line.count == 0)) 
         { text = (slot *) malloc(     (1+line.count)*sizeof(slot));}
    else { text = (slot *)realloc(text,(1+line.count)*sizeof(slot));}

    char * ptr = malloc(line.size*sizeof(char));
    text[line.count].row = ptr  ;
    text[line.count].size = line.size;
    memcpy(ptr,line.row,line.size);  

    line.count++; 
    return 0;
}

int main(int arc, char** argv)
{
    char *filename = "qwik.inp"; fp = fopen(filename,"r");
    int numb; int retval; int lastline;

    printf("107.c executing\n");

    line.count = 0;
    for (numb = 0 ; numb < 10; numb++) 
    {
    retval=readAline(); 
    if (retval == -1) {break;}
    lastline = line.count; 
    }

    printf("%d lines were read\n",lastline);

    int maxndx = lastline - 1;
    etxt(maxndx);
    replaceAline(5,maxndx);
    etxt(maxndx);

    if (fp != NULL) {fclose(fp);}
    return 0;
 }

