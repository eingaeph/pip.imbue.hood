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

void wind(int xmin, int xmax, int ymin, int ymax)
{
 
    int y;
    for (y = ymin; y < ymax + 1; y++) 
    {
    char *s = xmin + text[y].row; 

    int no;
    for ( no = 0; no + xmin < xmax + 1; no++)     
    {
    if (no>text[y].size ) {break;}; 
    if (*s == '\n')       {break;};
    printf("%c",*s); s++;
    }
    printf("\n");
    }
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

    printf("the string at text[].row:  %.*s", 
    text[line.count].size, text[line.count].row);  
    line.count++; 
    return 0;
}

int readAfile(char *filename)
{
    fp = fopen(filename,"r");
    int numb; int retval; int lastline;

    line.count = 0;
    for (numb = 0 ; numb < 20; numb++) 
    {
    retval=readAline(); 
    if (retval == -1) {break;}
    lastline = line.count;
    }
    return lastline;
}

int main(int arc, char** argv)
{
    char *filename = "test.dat";

    int lastline = readAfile(filename);
    printf("%d lines were read\n",lastline);

    wind(8,40,2,8);
 
    if (fp != NULL) {fclose(fp);}
    return 0;
 }

