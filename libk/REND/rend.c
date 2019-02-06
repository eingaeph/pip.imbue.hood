#include "../libk.h"
/*
    rend.c is a ../WARF/wind.c derivative

    note: wind.c is written in terms of text coordinates x,y
*/
void rend(int xmin, int xmax, int ymin, int ymax, int numbLines)
{
    assert(ymin >= 0); assert(ymax < glob.numbLines);
    assert(ymax >= ymin); assert((ymax - ymin) < glob.rows);

    int count = 0; char* rbuff;
    int y; int maxindex = 0;
    for (y =  ymin; y <= ymax; y++)
    {
     maxindex = maxindex + text[y].size;
    }
     maxindex = maxindex + 1000; rbuff = malloc(sizeof(char)*maxindex);
     assert(rbuff != NULL);

    for (y = ymin; y <= ymax; y++) 
    {
      int x; char* s = xmin + text[y].row;
      for ( x = xmin; x <= xmax; x++)
      {

//  following are two tests to determine whether *s should be stored in rbuf

        if (x>=text[y].size )  break; 
        assert(*s != '\n');

//  *s tests ok, assign it to rbuff[]


        rbuff[count] = *s; s++; count++; assert(count < maxindex);
       }

//  display the last line without a newline  which would move the cursor
//  below the window (virtural screen) possibly causing a virtual screen 
//  mismatch with the actual screen

    if(y != ymax) {rbuff[count] = '\n'; count++;}
    
//   printf("y = %d  x = %d size = %d  count = %d  \n",
//           y,x, (int) text[y].size, count); 
//   rbuff[count] = '\0'; printf("%s \n", rbuff); 
//   if(y > 2) exit(0);

     }

   count++; assert(count < maxindex);

   rbuff[count] = '\0'; printf("%s",rbuff);


    if(rbuff != NULL) free(rbuff);

}
