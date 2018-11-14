#include "../libk.h"

void arrow_right(void)
{
  possibleIxIy;

//  the maximum allowable ix is text[iy].size
 
  if(glob.ix == text[glob.iy].size) return;

     glob.ix++;
     possibleIxIy;

  return;
}

