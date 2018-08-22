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

int main(int arc, char** argv)
{
    char *filename = "qwik.inp"; fp = fopen(filename,"r");
    int numb; int retval; int lastline;

    printf("REAF executing\n");

    line.count = 0;
    for (numb = 0 ; numb < 10; numb++) 
    {
    retval=readAline(); 
    if (retval == -1) {break;}
    lastline = line.count;
    }

    printf("%d lines were read\n",lastline);

    char *s;
    int x = 9;
    int y = 3;
    printf("the string at text[].row:  %.*s", 
    text[y].size, text[y].row); 
    s = x + text[y].row;
    printf("single character <%c>\n",*s);
//    printf("%s\n",s);
 

    if (fp != NULL) {fclose(fp);}
    return 0;
 }

