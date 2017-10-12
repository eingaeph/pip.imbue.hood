#! /usr/bin/tcc -run

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum KEY_ACTION{    /* Following are multiple character codes */

  ARROW_LEFT = 1000,
  ARROW_RIGHT,
  ARROW_UP,
  ARROW_DOWN,
  DEL_KEY,
  HOME_KEY,
  END_KEY,
  PAGE_UP,
  PAGE_DOWN

};


struct 
{
int x,y;                   /* char no, line no, text coordinates */
int ix,iy;                 /* insertion point, text coordinates */
int xmin,xmax,ymin,ymax;   /* window edges in text coordinates  */ 
int u,v;                   /* screen char no, line no */
int cu,cv;                 /* cursor position in screen coordinates */
int umin,umax,vmin,vmax;   /* window endges in screen coordinates */
} S;

void arrow_right()
{

  printf("arrow right\n");
  if (S.ix == S.xmax || S.cu == S.umax) return;
  S.cu++; S.ix++; 

}

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
    char *filename = "qwik.inp";

    int lastline = readAfile(filename);
    printf("%d lines were read\n",lastline);

/*  x,y  text coordinates, charno, lineno */
    S.ix=0;
    S.iy=0;
    S.xmin=0;
    S.xmax=79;
    S.ymin=0;
    S.ymax=lastline;
/*  int u,v; screen char no, line no */
    S.cu=0;
    S.cv=0;
    S.umin=0;
    S.umax=79;
    S.vmin=0;
    S.vmax=79; 

    printf("cu = %d",S.cu);printf("  ix = %d\n",S.ix); 
    arrow_right(); 
    printf("cu = %d",S.cu);printf("  ix = %d\n",S.ix); 

    wind(8,40,2,8);
 
    if (fp != NULL) {fclose(fp);}
    return 0;
 }

