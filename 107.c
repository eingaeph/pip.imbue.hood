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
    slot *old;
    slot *new;

    char *ptr;

void replaceAline(int inpt, int lastline)
{

    slot newline;
    ptr = "Hello world!\n";
    newline.row = ptr;
    newline.size = strlen(ptr);
    
    int j;
    for (j = 0; j < lastline; j++) 
      {if (j != inpt) {new[j] = old[j];}
       else           {
                       new[j] = newline;
                       if (old[j].row != NULL)  free(old[j].row);                                               
                      }
      }

    return;
}

int readAline(void)
{
    line.row = NULL; linecap = 0;
    line.size = getline (&line.row, &linecap, fp); 

    if (line.size == -1) {return line.size;}

    if((line.count == 0)) {text = malloc(sizeof(slot));}
    else {text = realloc(text,(1+line.count)*sizeof(slot));}

    char * ptr = malloc(line.size*sizeof(char));
    text[line.count].row = ptr  ;
    text[line.count].size = line.size;
    memcpy(ptr,line.row,line.size);

//    printf("at text[%d].row:  %.*s",
//    line.count,
//    text[line.count].size, text[line.count].row);  
    line.count++; 
    return 0;
}

int main(int arc, char** argv)
{
    char *filename = "qwik.inp"; fp = fopen(filename,"r");
    int numb; int retval; int lastline;

    printf("\n107.c executing\n");

    line.count = 0;
    for (numb = 0 ; numb < 10; numb++) 
    {
    retval=readAline(); 
    if (retval == -1) {break;}
    lastline = line.count;
    }

    printf("\n%d lines were read\n\n",lastline);
    
    int y;
    for (y = 0; y < lastline; y++) {
    printf("text[%d].row:  %.*s", 
    y,text[y].size, text[y].row);      }
    
    old = malloc((1+lastline)*sizeof(slot));
    new = malloc((1+lastline)*sizeof(slot)); 
    old = text;

    replaceAline(4,lastline);

    printf("\n");
    printf("the string at new[3].row:  %.*s", 
    new[3].size, new[3].row); 

    printf("the string at new[4].row:  %.*s", 
    new[4].size, new[4].row); 

    if (fp != NULL) {fclose(fp);}
    printf("\n"); return 0;
 }

