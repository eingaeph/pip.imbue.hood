#include "../libk.h"
/*
    wind.c
    function print window into text onto screen 
    window coordinates 
    text coordinates x,y
    screen coordinates u,v
    note: wind.c is written in terms of text coordinates x,y
*/
void wind(int xmin, int xmax, int ymin, int ymax, int numblines)
{
    assert(ymax >= ymin); assert(ymin < numblines);
    if (ymax >= numblines) ymax=numblines - 1;

    for (int y = ymin; y < ymax + 1; y++) 
    {

//  description of for usage
//  for (once first; before each conditional exec; after exec)

      int x; char* s = xmin + text[y].row;
      for ( x = xmin; x <= xmax; x++)   
      {
        if ((x - xmin + 1)>text[y].size ) {break;}; 
        if (*s == '\n')       {break;};
        printf("%c",*s); s++;
      }
      printf("\n");
    }
   
}


