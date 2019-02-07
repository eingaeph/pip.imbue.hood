#include "../libk.h"
/*
    rend.c is a ../WARF/wind.c derivative

    note: wind.c is written in terms of text coordinates x,y
*/
void rend(int xmin, int xmax, int ymin, int ymax, int numbLines)
{
    assert(ymin >= 0); assert(ymax < glob.numbLines);
    assert(ymax >= ymin); assert((ymax - ymin) < glob.rows);

    int count = 0; char* abuff; char* rbuff;
    int y; int maxindex = 0;
    for (y =  ymin; y <= ymax; y++)
    {
     maxindex = maxindex + text[y].size;
    }
     maxindex = maxindex + 1000; 
     abuff = malloc(sizeof(char)*maxindex); assert(abuff != NULL);

     rbuff = malloc(sizeof(char)*maxindex); assert(rbuff != NULL);


    for (y = ymin; y <= ymax; y++) 
    {
      int x; char* s = xmin + text[y].row;
      for ( x = xmin; x <= xmax; x++)
      {

//  following are two tests to determine whether *s should be stored in rbuf

        if (x>=text[y].size )  break; 
        assert(*s != '\n');

//  *s tests ok, assign it to rbuff[]


        abuff[count] = *s; s++; count++; assert(count < maxindex);
       }

//  display the last line without a newline  which would move the cursor
//  below the window (virtural screen) possibly causing a virtual screen 
//  mismatch with the actual screen

    if(y != ymax) {abuff[count] = '\n'; count++;}
    
//   printf("y = %d  x = %d size = %d  count = %d  \n",
//           y,x, (int) text[y].size, count); 
//   rbuff[count] = '\0'; printf("%s \n", rbuff); 
//   if(y > 2) exit(0);

     }

   count++; assert(count < maxindex);
   abuff[count] = '\0'; 

// precede it with  the <esc>[31m escape sequence
// and follow it by the <esc>[39m sequence.

 
   char* query = "find";
   int jndex, next;
   next = 0;
   while(strstr(abuff + next,query) != NULL) 
     {
      jndex = (int) (strstr(abuff + next,query) - abuff);
      printf("index = %d  next = %d\n",jndex,next);
      next = jndex + strlen(query);
      } 
   exit(0);    

   int na; int nr = 0;
   for( na = 0; na <= count; na ++)
   {
     if (na ==5 )  { memcpy(rbuff+nr,"\x1b[31m", 5); nr = nr + 5;}
     if (na ==15 ) { memcpy(rbuff+nr,"\x1b[39m", 5); nr = nr + 5;}
     rbuff[nr] = abuff[na]; nr++;
   }

   assert(nr < maxindex);
   printf("%s",rbuff);

    if(abuff != NULL) free(abuff);
    if(rbuff != NULL) free(rbuff);

}
