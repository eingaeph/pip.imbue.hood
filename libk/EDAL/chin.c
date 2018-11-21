// chin  set insertion point after one byte character insert

#include "../libk.h"

void chin(char c, int fetch) //fetch text[fetch].row
{
  assert(glob.iy == fetch); possibleLine; possibleIxIy;
  
  int limit = text[fetch].size + 1 ; 
  char *new = malloc((limit)*sizeof(char));
  char *orig = text[fetch].row;

  int no; int mo = 0; 
  for (no = 0 ; no < limit; no++)
    {
     if (no != glob.ix)  {new[no] = orig[mo];mo++;}
     else                {new[no] = c; }
    }

  if (text[fetch].row != NULL) free(text[fetch].row); 
  text[fetch].row = new; 
  text[fetch].size = limit; 
  glob.ix++; 

  possibleLine; possibleIxIy;
  return;

}

