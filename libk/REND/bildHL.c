#include "../libk.h"

void bildHL(char* abuff, char** xbuff, int* rlim)
{
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

   char* rbuff = *xbuff; //rbuf is made available in the calling routine

   int na; int nr = 0; int limit = counter; counter = 0; 
   for( na = 0; na <= limit; na ++)
   {

     if (na ==hl[counter].index)  
        { 
          char* ptr = hl[counter].change;
          memcpy(rbuff+nr,ptr,strlen(ptr)); 
          nr = nr + strlen(ptr);
          counter++;
        }
     rbuff[nr] = abuff[na]; nr++;
   }
 
   *rlim = nr;

}
