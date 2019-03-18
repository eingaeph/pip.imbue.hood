#include "../libk.h"

// build arg3[].HLindex and arg3[].HLchange
// int look is the offset: where to start looking for the next occurence of query
// of an opening brace

void bildHL_1(char* query, char* abuf, int* look)
{

// highlight segment with  the <esc>[31m escape sequence and <esc>[39m sequence.

   char* red     = "\x1b[31m"; //precede HL sequence 
   char* revert  = "\x1b[39m"; //follow  HL sequence
 
//   typedef struct {int HLindex; char* HLchange;} highlight;
//   highlight* arg3;

   arg3 = malloc(50*sizeof(highlight));

      // int look          the offset to start looking for the next occurence of query
      // int ndex;         the index of the current found query
      int counter = 0;   //the number of occurrences, before the current 
printf("bildHL_1 strlen abuf = %d\n",(int)strlen(abuf));
      while(strstr(abuf + *look,query) != NULL) 
        {
         int ndex = (int) (strstr(abuf + *look,query) - abuf);

         arg3[counter].HLindex = ndex;     arg3[counter].HLchange = red;    
         *look = ndex + strlen(query);
printf("look is changed %d, counter = %d \n",*look, counter);
         arg3[counter].HLindex = *look;     arg3[counter].HLchange = revert; 
         counter++;
        }   
      return; 

   return; // the default (noaction)
}
