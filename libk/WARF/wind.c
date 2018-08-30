#include "gather.h"

void wind(int xmin, int xmax, int ymin, int ymax, int numblines)
{
    assert(ymax >= ymin); assert(ymin < numblines);
    if (ymax >= numblines) ymax=numblines - 1;

    for (int y = ymin; y < ymax + 1; y++) 
    {

//  description: for (once first; before each conditional exec; after exec)

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


