#include "../libk.h"

// build arg3[].HLindex and arg3[].HLchange
// int look is the offset: where to start looking for the next occurence 
// of an opening brace

void bildHL_2(int look, char* abuf)
{

// highlight segment with  the <esc>[31m escape sequence and <esc>[39m sequence.

   char* red     = "\x1b[31m"; //precede HL sequence 
   char* revert  = "\x1b[39m"; //follow  HL sequence
 
//   typedef struct {int HLindex; char* HLchange;} highlight;
//   highlight* arg3;

   arg3 = malloc(50*sizeof(highlight));

// highlight completed braces sequence (BRAS)
  
   char* s = abuf;
   int i=0;   /* i indicates the depth of bracketing */ 
   int k = 0; /* k indicates the number of bracket initiated */  
   int ndex;  /* ndex is the index into abuf (and s) */

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

   return; // the default (noaction)
}
