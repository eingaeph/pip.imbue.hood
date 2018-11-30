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

// check for a valid query

   assert(strlen(query) >= 0);
   if (strlen(query) == 0) 
        {
          possibleLine; possibleIxIy;
          return;
        }

// check that the current line is long enough to contain query

   if(text[glob.iy].size - strlen(query) <= 0)
         {
           possibleLine; possibleIxIy;
           return;
         }

// check the current line for the search string

   char* match = memmem(text[glob.iy].row,
                        text[glob.iy].size,
                        query,
                        strlen(query));

// starting search in a line containing query
int iw = 4234567; printf("at a\n\r"); waiter(iw);

   if (match != NULL) 
      { 
printf("at b\n\r"); waiter(iw);
        int testa = ( (int) (match - text[glob.iy].row) == 0); //check for immediate find
printf("testa = %d\n\r",testa); waiter(iw);
        if (!testa) 
              {
               glob.ix = (int) (match - text[glob.iy].row);
               possibleLine; possibleIxIy;
               return;
              }
printf("at c\n\r");  waiter(iw);
// tests for immediate find

        int lenrest = text[glob.iy].size - 2*strlen(query) -glob.ix;
        int testb = (lenrest <=0 );
        char* rest  = text[glob.iy].row + glob.ix + strlen(query);
        char* natch = NULL;
        if (!testb) natch = memmem(rest,
                                   lenrest,
                                   query,
                                   strlen(query));
        int testc = (natch == NULL); 

// skip immediate find in first line check 

         if (!testb && !testc )
             {
               assert( (int) (natch - rest) > 0);
               glob.ix = glob.ix + strlen(query) + (int) (natch - rest); 
               possibleLine; possibleIxIy;
               return;  
              } 
   
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

