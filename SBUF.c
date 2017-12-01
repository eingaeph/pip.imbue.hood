#! /usr/bin/tcc -run

/*** construct scroll ready screen buffer ***/
 
//  y = 0,1,2 ... (text buffer   first line, second line, ...)
//  x = 0,1,2 ... (screen buffer first character in line y, ...) 

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

    slot  line;
    slot* text;

void screenBuffer(int star, int stop)
{
    printf("%s","screenBuffer at work\n");
    slot* display = (slot *) malloc(     (25)*sizeof(slot));
    for (int i=0; i<25; i++) {display[i].size  =   3;
                              display[i].row   = "~\r\n";
                              display[i].count =   0;}
    int i; int dy = -1; 
    for (int i = star; i<(stop+1); i++)
         {dy++ ; display[dy] = text[i];}

    dy = -1 ;
    for (int i = 0; i< 23; i++)
         {
          dy++ ;
          int stringLength = display[dy].size;
          char* pointerToString = display[dy].row;
          printf("%.*s", stringLength, pointerToString);
         }

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

   printf("%s","here i should be\n");
   screenBuffer(1,3);
 
}



