#include "../libk.h"

void arrow_right(void)
{
  possibleIxIy;
  if(glob.ix < text[glob.iy].size ) 
    {
     glob.ix++;
     possibleIxIy;
    }
  return;
}
