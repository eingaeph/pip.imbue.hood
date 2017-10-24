#! /usr/bin/tcc -run

/* 
   edit emphasized brace open_s and close_s
*/

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

    int braceno = 0;

void outline(int y)
{
    int xmax = 80;
    char *s = text[y].row;
    int no;
    for ( no = 0; no < xmax + 1; no++)     
    {  
    if (no>text[y].size ) {break;};
    if (*s == '\n')       {break;};
    printf("%c",*s); s++;
    }       
}

void parser(int y)
{
    int xmax = 80;
    char *s = text[y].row;
    int no;
    for ( no = 0; no < xmax + 1; no++)     
    {  
    if (no>text[y].size ) {break;};
    if (*s == '\n')       {break;};
    int testa = (*s == '{');
    int testb = (*s == '}');
    if (testa) braceno ++;
    if (testb) braceno --;
    int testc = (*s != ' ' && braceno != 0);
    if (testc) printf("%d",braceno); 
    else       printf(" ");
    s++;
    }       
}


void bracket (int lastline)
{
    int xmin, xmax, ymin, ymax, y;

    xmin = 0; xmax = 80;
    ymin = 0; ymax = lastline;
    printf("lastline = %d\n",lastline);
    for (y = ymin; y < ymax; y++) 
    {
/*    char *s = xmin + text[y].row; 

    int no;
    for ( no = 0; no + xmin < xmax + 1; no++)     
    {
    if (no>text[y].size ) {break;}; 
    if (*s == '\n')       {break;};
    printf("%c",*s); s++;          
    }
*/
    outline(y); printf("\n"); parser(y); printf("\n");
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

//    printf("the string at text[].row:  %.*s", 
//    text[line.count].size, text[line.count].row);  
    line.count++; 
    return 0;
}

int readAfile(char *filename)
{
    fp = fopen(filename,"r");
    int numb; int retval; int lastline;

    line.count = 0;
    for (numb = 0 ; numb < 50; numb++) 
    {
    retval=readAline(); 
    if (retval == -1) {break;}
    lastline = line.count;
    }
    return lastline;
}

int main(int arc, char** argv)
{
    char *filename = "bacin.dat";

    int lastline = readAfile(filename);
    printf("%d lines were read\n",lastline);
    bracket(lastline);

 
    if (fp != NULL) {fclose(fp);}
    return 0;
 }
