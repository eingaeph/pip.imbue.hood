#include "../libk.h"

void del_key(int fetch)
{
  possibleIxIy;
  int testy = fetch; testy = testy; possibleLine;
  int testa = (text[fetch].size == 0); // first edge case
  if (testa) {assert(glob.ix == 0);   
              assert(text[fetch].row == NULL);
              return;}

  int testb = (text[fetch].size == 1); // second edge case
  if (testb) {free(text[fetch].row);
              text[fetch].row = NULL;
              text[fetch].size = 0;
              glob.ix = 0; 
              return;}

  assert(text[fetch].size > 1); assert(text[fetch].row != NULL);

  int limit = text[fetch].size - 1 ; 
  char *new; new = malloc((limit)*sizeof(char));

  char *chng = new;
  char *orig = text[fetch].row;

  int no; 
  for (no = 0 ; no <= limit; no++)
    {
     if (no != glob.ix)  {*chng = *orig; chng++; orig++;}
     else                { orig++ ;} // skipping
    }

  free(text[fetch].row); 
  text[fetch].row = new; text[fetch].size = limit; 

  if (glob.ix >= limit) glob.ix = limit - 1;

  assert(glob.ix >= 0);
  testy = fetch; possibleLine;

  return;

}

