#include "../libk.h"
/*
    rend.c is a ../WARF/wind.c derivative
    note: both are written in terms of text coordinates x,y
*/

void bildRBUF(char** abuf, char** rbuf)
{
    int ymin = glob.ymin;
    int ymax = glob.ymax;
    assert(ymin >= 0); assert(ymax < glob.numbLines);
    assert(ymax >= ymin); assert((ymax - ymin) < glob.rows);

    int count = 0; int look = 0;
    int y; int maxindex = 0;
    for (y =  ymin; y <= ymax; y++)
    {
     maxindex = maxindex + text[y].size;
    }
     maxindex = maxindex + 1000; 

   char* rbuff = malloc(maxindex*sizeof(char));
   int na; int nr = 0; int limit = strlen(abuf); int counter = 0; 
   for( na = 0; na <= limit; na ++)
   {

     if (na ==arg3[counter].HLindex)  
        { 
          char* ptr = arg3[counter].HLchange;
          memcpy(rbuff+nr,ptr,strlen(ptr)); 
          nr = nr + strlen(ptr);
          counter++;
        }
     rbuff[nr] = abuf[na]; nr++;
   }

   assert(nr < maxindex);
   printf("%s",rbuff);

    if(abuff != NULL) free(abuff);
    if(rbuff != NULL) free(rbuff);
    if(arg3  != NULL) free(arg3);

}
