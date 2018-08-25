#include "gather.h"

void wind(int xmin, int xmax, int ymin, int ymax, int lastline)
{
 
    int y;
    if (ymax > lastline-1) ymax = lastline-1;
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


