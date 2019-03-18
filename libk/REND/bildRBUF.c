#include "../libk.h"
/*
    insert arg3[counter].HLchange
*/

void bildRBUF(char* abuf, char* rbuf)
{
 
printf("rbuf strlen abuf = %d\n",(int)strlen(abuf));

   int na; int nr = 0; int limit = strlen(abuf); int counter = 0; 
   for( na = 0; na <= limit; na ++)
   {

     if (na ==arg3[counter].HLindex)  
        { 
printf("rbuf counter = %d \n",counter);
          char* ptr = arg3[counter].HLchange;
          memcpy((rbuf+nr),ptr,strlen(ptr) ); 
          nr = nr + strlen(ptr);
          counter++;
        }
     rbuf[nr] = abuf[na]; nr++;
   }

//   assert(nr < maxindex);

rbuf[nr] = '\0';

}
