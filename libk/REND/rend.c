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

//  *s tests ok, assign it to abuff[]

        abuff[count] = *s; s++; count++; assert(count < maxindex);
       }

//  display the last line without a newline  which would move the cursor
//  below the window (virtural screen) possibly causing a virtual screen 
//  mismatch with the actual screen

    if(y != ymax) {abuff[count] = '\n'; count++;}
    
     }

   count++; assert(count < maxindex);
   abuff[count] = '\0'; 

// build hl[]
// precede it with  the <esc>[31m escape sequence
// and follow it by the <esc>[39m sequence.

   char* red     = "\x1b[31m";
   char* revert  = "\x1b[39m";
   typedef struct {int index; char* change; int leng;} high;
   high hl[50];
 
   char* query = "find";
   int look = 0;      //the offset to start looking for the next occurence of query
   int ndex;          //the index of the current found query
   int counter = 0;   //the number of occurrences, before the current 
  
   while(strstr(abuff + look,query) != NULL) 
     {
      ndex = (int) (strstr(abuff + look,query) - abuff);

      hl[counter].index = ndex;     hl[counter].change = red;    counter++;
      look = ndex + strlen(query);
      hl[counter].index = look;     hl[counter].change = revert; counter++;
      }    
/*
   int arb;
   for (arb = 0; arb < counter; arb++)
   {
    printf("%d\n",hl[arb].index);
   }
   exit(0);
*/

   int na; int nr = 0; counter = 0;
   for( na = 0; na <= count; na ++)
   {
//     if (na ==5 )  { memcpy(rbuff+nr,red,   strlen(red)   ); nr = nr + strlen(red   );}
//     if (na ==15 ) { memcpy(rbuff+nr,revert,strlen(revert)); nr = nr + strlen(revert);}

     if (na ==hl[counter].index)  
        { 
          char* ptr = hl[counter].change;
          memcpy(rbuff+nr,ptr,strlen(ptr)); 
          nr = nr + strlen(ptr);
          counter++;
        }
     rbuff[nr] = abuff[na]; nr++;
   }

   assert(nr < maxindex);
   printf("%s",rbuff);

    if(abuff != NULL) free(abuff);
    if(rbuff != NULL) free(rbuff);

}
