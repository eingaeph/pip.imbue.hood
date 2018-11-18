#include "../libk.h"
/*
    wind.c
    write a window into text to the screen 
    window coordinates require intital cursor at top left
    that is text coordinate position xmin, ymin 
      is at the top left at the screen
    
    note: wind.c is written in terms of text coordinates x,y
*/
void wind(int xmin, int xmax, int ymin, int ymax, int numbLines)
{
    assert(ymin >= 0); assert(ymax < glob.numbLines);
    assert(ymax >= ymin); assert((ymax - ymin) < glob.rows);

    for (int y = ymin; y <= ymax; y++) 
    {

//  description of <for> idiom
//  for (once first; before each conditional exec; after exec)

      int x; char* s = xmin + text[y].row;
      for ( x = xmin; x <= xmax; x++)   
      {

//  following are two tests to determine whether *s should be written
//  to the screen

        if (x>=text[y].size )  {break;}; 
        if (*s == '\n')        {break;};

//  *s tests ok, write it to the screen

        printf("%c",*s); s++;
      }

//  the next statement serves to omit the newline after writing the
//    last line of the window
//  otherwise the top line of the window gets pushed off the screen
//    when the window should exactly fit the screen

      if(y != ymax) printf("\n"); else fflush(stdout);

//  the final else fflush displays the last line without a newline 
//  which would move the cursor to the next line
    }
     
}


