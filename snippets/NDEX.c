#! /usr/bin/tcc -run

//  input file into text structure
//  access characters by x,y 
//  y = 0,1,2 ... (first line, second line, ...)
//  x = 0,1,2 ... (first character in line y, ...) 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    printf("\n%s executing\n\n",argv[0]);

    char *filename = "NDEX.dat"; fp = fopen(filename,"r");
    int lastline;

    line.count = 0;
    while((readAline() != -1)) {lastline = line.count;}

    for (int y = 0; y < lastline;      y++)
   {
    for (int x = 0; x < text[y].size;  x++)
    {char ch = text[y].row[x];    printf("%c",ch);}
   }

}



