#include "../libk.h"

int end_key(void)
{
  possibleIxIy;
  if (text[glob.iy].size == 0) 
     {glob.ix = 0; return 0;} 

  glob.ix = text[glob.iy].size - 1; 
  possibleIxIy;
  return 0;

}
