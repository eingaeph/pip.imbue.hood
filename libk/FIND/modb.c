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
    printf("query = %s\n\r",query); 
   }

// check the current line for the search string

   char *s = text[glob.iy].row + glob.ix;
   int size = text[glob.iy].size - glob.ix;
   char *match = memmem(s,size,query,strlen(query)); 

   int testa = (int) (match - text[glob.iy].row);
   int testb = (match != NULL);
   int testc = (testa != glob.ix);        
   if (testb && testc) // match occurs but not at the insertion point
        {
         glob.ix = (int) (match -text[glob.iy].row);
         possibleLine; possibleIxIy;
         return;
        } 

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

