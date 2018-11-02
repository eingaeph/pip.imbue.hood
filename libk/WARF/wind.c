#include "../libk.h"
/*
    wind.c
    function print window into text onto screen 
    window coordinates require intital cursor at top left
    that is text coordinate position xmin, ymin 
      is at the top left at the screen
    
    note: wind.c is written in terms of text coordinates x,y
*/
void wind(int xmin, int xmax, int ymin, int ymax, int numbLines)
{
    assert(ymin >= 0); assert(ymax < glob.numbLines);
    assert(ymax >= ymin); assert((ymax - ymin) < glob.rows);

    printf("wind.c starting"); fflush(stdout); exit(0); 

    for (int y = ymin; y <= ymax; y++) 
    {

//  description of for idiom
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


