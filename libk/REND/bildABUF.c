#include "../libk.h"
/*
    rend.c is a ../WARF/wind.c derivative
    note: both are written in terms of text coordinates x,y
*/

void bildABUF(char* abuf, int* look, int maxindex)
{
    int count = 0;
    int y; 
    int xmin = glob.xmin; int xmax = glob.xmax;
    int ymin = glob.ymin; int ymax = glob.ymax;
    for (y = ymin; y <= ymax; y++) 
    {
      int x; char* s = xmin + text[y].row;
      for ( x = xmin; x <= xmax; x++)
      {

//  following are two tests to determine whether *s should be stored in abuf

        if (x>=text[y].size )  break; assert(*s != '\n');

//  here *s tests ok, assign it to abuf[]

        if (x == glob.ix && y == glob.iy) *look = count;
        abuf[count] = *s; s++; count++; assert(count < maxindex);
       } //end inner for loop

//  test whether to display the last line without a newline  
//  which otherwise would move the cursor below the window (virtural screen) 
//  possibly causing a virtual screen mismatch with the actual screen

      if(y != ymax) {abuf[count] = '\n'; count++;}    
     }  //end outer for loop

printf("bildABUF count = %d\n",count);
   abuf[count] = '\0'; 
printf("bildABUF the length of abuf is %d \n",(int) strlen(abuf));
   return;
}

