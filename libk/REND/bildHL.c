#include "../libk.h"

// build arg3[].HLindex and arg3[].HLchange
// int look is the offset: where to start looking for the next occurence of query
// of an opening brace

void bildHL(int option, int look, char* abuff)
{

// highlight segment with  the <esc>[31m escape sequence and <esc>[39m sequence.

   char* red     = "\x1b[31m"; //precede HL sequence 
   char* revert  = "\x1b[39m"; //follow  HL sequence
 
//   typedef struct {int HLindex; char* HLchange;} highlight;
//   highlight* arg3;

   arg3 = malloc(50*sizeof(highlight));

   if (option == 1)   // highlight query (FIND)
   {
      char* query = "find";
      // int look  **      the offset to start looking for the next occurence of query
      int ndex;          //the index of the current found query
      int counter = 0;   //the number of occurrences, before the current 
  
      while(strstr(abuff + look,query) != NULL) 
        {
         ndex = (int) (strstr(abuff + look,query) - abuff);

         arg3[counter].HLindex = ndex;     arg3[counter].HLchange = red;    
         counter++;
         look = ndex + strlen(query);
         arg3[counter].HLindex = look;     arg3[counter].HLchange = revert; 
         counter++;
        }   
      return; 
   }

   if (option == 2)   // highlight completed braces sequence (BRAS)
   {
        char* s = abuff;
        int i=0;   /* i indicates the depth of bracketing */ 
        int k = 0; /* k indicates the number of bracket initiated */  
        int ndex;  /* ndex is the index into abuff (and s) */
        for (ndex=0; s[ndex]; ndex++) 
          {
           if ( (s[ndex]== '{') && (k == 0)) 
             {arg3[0].HLindex = ndex;    arg3[0].HLchange = red; }
           if (s[ndex]=='{')  {i++; k++;}
           if (s[ndex]=='}')  i--;
           if ((i == 0) && (k > 0)) break;
          };    
        arg3[1].HLindex = ndex+1;    arg3[1].HLchange = revert; 
//      if (i == 0) printf("the bracket was closed with k = %d \n",k);
        return;
   }

   return; // the default (noaction)
}
