#include "../libk.h"

void modb(int retval)
{
   char query[100]; char *s = &query[0];
   printf("search mode\n\r"); 
   while(1)
   {
    int retval = ReadKey(); if (retval == CTRL_S) break;
    char c = retval;         // retrieve a 1 byte character 
                             // from a 4 byte intege
    *s = c; s++;
    *s = '\0';
    printf(CursorToTopLeft "\x1b[999B" "query = %s",query);  fflush(stdout);
   }

// check for a valid query, or a zero length query

   assert(strlen(query) >= 0);
   if (strlen(query) == 0) 
        {
          possibleLine; possibleIxIy;
          return;    //  query length is zero so return, without changing ix,iy
        }

// following is a do {} while(0) containg the initial line edge case
// exit the do while curly brackets by returns or breaks 

do {
   
// check the first line for the search string

    char* match = memmem(text[glob.iy].row,
                         text[glob.iy].size,
                         query,
                         strlen(query));

    if (match == NULL) break; // keep looking in other lines

// starting search in a line containing query

    int ndx = (int) (match - text[glob.iy].row);

//  check for a match after the insertion point, which would be a valid find 

    int testa = (ndx > glob.ix);  //check for match after the cursor
    if (testa)   //match after the cursor 
              {
               glob.ix = ndx;   // valid match, reset cursor position ix
               possibleLine; possibleIxIy;
               return;
              }

// an invalid match was found but there still may be 
// a valid match 
// toward the end of the firs line
 
// look for the index of query in the rest of the line 

    char* rest = text[glob.iy].row + glob[ix]; 
    int leng = text[glob.iy].size - glob[ix] - 1;   

    if (leng >= strlen(query)) {break;} // keep looking in other lines 

    match = memmem(rest,leng,query,strlen(query));

    if (match == NULL) break;  // keep looking in other lines 

// now there is a valid match, reset glob.ix and return 
    glob.ix = glob.ix + int(match - rest)

   } while (0)  // end of the first line edge case


// loop through text searching for query, not to be found in the first line i=0

  int i;
  for (i = 1; i < glob.numbLines; i++) 
   {int j = i + glob.iy; 
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

