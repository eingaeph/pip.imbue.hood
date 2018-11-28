#include "../libk.h"

void modb(int retval)
{
   char query[100]; char *s = &query[0];
printf("here i am\n\r"); 
   while(1)
   {
    int retval = ReadKey(); if (retval == CTRL_S) break;
    char c = retval;         // retrieve a 1 byte character 
                             // from a 4 byte intege
    *s = c; s++;
    *s = '\0';
    printf("query = %s\n\r",query); 
   }

// loop through text searching for query
  int i;
  for (i = 0; i < glob.numbLines; i++) 
   {int j = i + glob.iy; 
    if (j >= glob.numbLines) j = j - glob.numbLines; 
    char *match = strstr(text[j].row, query);
    if (match) 
              {
                glob.iy = j; 
                glob.ix = (int) (match - text[j].row);
                return;
              }
    }

}

