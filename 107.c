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

void replaceAline(void)
{

    slot *old  = (slot *)malloc(10*sizeof(slot));
    slot *new  = (slot *)malloc(10*sizeof(slot));

    slot newline;
    char *ptr = "Hello World!\n";
    newline.row = ptr;
    newline.size = strlen(ptr);

    old = text;


    int i,j,k; i = 0; j = 0; k = 0;
    for (i = 0; i < 10; i++) 
      {if (i != 3) {new[j] = old[k]; j++; k++;}
       else        {new[j] = newline;j++; k++;}
      }

    free(text);
    text = (slot *)malloc(10*sizeof(slot));
    text = new;

    free(old); free(new);
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

//    printf("the string at text[].row:  %.*s", 
//    text[line.count].size, text[line.count].row);  

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

    int y =3;
    printf("the string at text[%d].row:  %.*s",
    y,text[y].size, text[y].row); 

    replaceAline();

    y =3;
    printf("the string at text[%d].row:  %.*s",
    y,text[y].size, text[y].row); 

    if (fp != NULL) {fclose(fp);}
    return 0;
 }

