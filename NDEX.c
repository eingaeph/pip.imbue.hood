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

char fetc(int x, int y)
{
    char *ps; 
    ps = text[y].row;  // the address of an array of characters
    char ch = ps[x];   // the x_th character in the array ps
    return ch;
}

int main(int arc, char** argv)
{
    char *filename = "NDEX.dat"; fp = fopen(filename,"r");
    int numb; int retval; int lastline;

    printf("NDEX.c executing\n\n");

    line.count = 0;
    for (numb = 0 ; numb < 100; numb++) 
    {
    retval=readAline(); 
    if (retval == -1) {break;}
    lastline = line.count; 
    }

//    printf("%d lines were read\n",lastline);

    for (int y = 0; y < lastline;      y++)
   {
    for (int x = 0; x < text[y].size;  x++)
    {char ch = fetc(x,y);    printf("%c",ch);}
   }
    

}



