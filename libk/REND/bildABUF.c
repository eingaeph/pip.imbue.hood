#include "../libk.h"
/*
    rend.c is a ../WARF/wind.c derivative
    note: both are written in terms of text coordinates x,y
*/

void bildABUF(char** abuf, int* look)
{
    int xmin = glob.xmin;
    int xmax = glob.xmax;
    int ymin = glob.ymin;
    int ymax = glob.ymax;

    assert(ymin >= 0); assert(ymax < glob.numbLines);
    assert(ymax >= ymin); assert((ymax - ymin) < glob.rows);

    int count = 0; *look = 0;
    int y; int maxindex = 0;
    for (y =  ymin; y <= ymax; y++)
    {
     maxindex = maxindex + text[y].size;
    }
     maxindex = maxindex + 1000; 
     char* abuff = malloc(sizeof(char)*maxindex); assert(abuff != NULL);

    for (y = ymin; y <= ymax; y++) 
    {
      int x; char* s = xmin + text[y].row;
      for ( x = xmin; x <= xmax; x++)
      {

//  following are two tests to determine whether *s should be stored in abuff

        if (x>=text[y].size )  break; assert(*s != '\n');

//  here *s tests ok, assign it to abuff[]

        if (x == glob.ix && y == glob.iy) *look = count;
        abuff[count] = *s; s++; count++; assert(count < maxindex);
       } //end inner for loop

//  test whether to display the last line without a newline  
//  which otherwise would move the cursor below the window (virtural screen) 
//  possibly causing a virtual screen mismatch with the actual screen

      if(y != ymax) {abuff[count] = '\n'; count++;}    
     }  //end outer for loop

   count++; assert(count < maxindex);
   abuff[count] = '\0'; 
   return;
}
