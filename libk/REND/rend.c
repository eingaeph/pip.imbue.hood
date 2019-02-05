#include "../libk.h"
/*
    rend.c is a ../WARF/rend.c derivative

    note: wind.c is written in terms of text coordinates x,y
*/
void rend(int xmin, int xmax, int ymin, int ymax, int numbLines)
{
    assert(ymin >= 0); assert(ymax < glob.numbLines);
    assert(ymax >= ymin); assert((ymax - ymin) < glob.rows);

    int rmaxindex = 0; char rbuff[5000];
    for (int y = ymin; y <= ymax; y++) 
    {
      int x; char* s = xmin + text[y].row;
      for ( x = xmin; x <= xmax; x++)   
      {

//  following are two tests to determine whether *s should be written
//  to the screen

        if (x>=text[y].size )  {break;}; 
        if (*s == '\n')        {break;};

//  *s tests ok, write it, move it to rbuff[]

        rbuff[rmaxindex] = *s; s++; rmaxindex++;
       }

//  the next statement serves to omit the newline after writing the
//    last line of the window (virtual screen)
//  otherwise the top line of the window gets pushed off the screen
//    when the virtual screen should exactly fit the actual bscreen

      if(y != ymax) {rmaxindex++, rbuff[rmaxindex] = "\n"; 

//  displays the last line without a newline  which would move the cursor 
//  below the window (virtural screen) causing a virtual screen actual screen
//  mismatch

    }
     
}

