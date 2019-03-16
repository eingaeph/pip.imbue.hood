#include "../libk.h"

// modb.c: a driver routine: controls the query find functionality

void modb(char* query)
{
   char* match;
 
// if query length is zero return, without changing ix,iy

   if (strlen(query) == 0) { possibleLine; possibleIxIy; return; }

// the followiing do {} while(0) block treats the initial line at glob.iy
// edge case
// exiting the {} block is by 3 breaks and 2 returns

   do {
   
// check the first line for the search string

        match = memmem(text[glob.iy].row,
                text[glob.iy].size,
                query,
                strlen(query));

        if (match == NULL) break; // keep looking in other lines

// starting search in a line containing query

        int ndx = (int) (match - text[glob.iy].row);

//  check for a match after the insertion point, which would be a valid find 

        int testa = (ndx > glob.ix);  
        if (testa)   //valid match after the cursor 
                   { glob.ix = ndx;   // valid match, reset cursor position ix
                     possibleLine; possibleIxIy;
                     return;
                   }

// the previous query math was invalid but there still may be 
// a valid match further toward the end of the first line
 
// look for a query match in the rest of the line 

         char* rest = text[glob.iy].row + glob.ix +1; 
         int leng = text[glob.iy].size - glob.ix - 1;   

         if (leng < strlen(query)) {break;} // keep looking in other lines 

         match = memmem(rest,leng,query,strlen(query));

         if (match == NULL) break;  // keep looking in other lines 

// now there is a valid match, reset glob.ix and return 

         glob.ix = (int) (match - text[glob.iy].row); possibleLine; possibleIxIy;
         return;

      }  while (0);  // end of the first line edge case


// loop through text searching for valid query match, 
// which match was not found in the first line i=0

   int i;
   for (i = 1; i < glob.numbLines; i++) 
       { 
         int j = i + glob.iy; 
         if (j >= glob.numbLines) j = j - glob.numbLines; 
         match = memmem(text[j].row, text[j].size, query,strlen(query));
         if (match) 
                   {
                     glob.iy = j; 
                     glob.ix = (int) (match - text[j].row);
                     printf("match = %d\n\r", *match);
                     printf("ix = %d\n\r",glob.ix);
                     return;
                   }
      }

}

