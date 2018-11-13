#include "../libk.h"

void arrow_right(void)
{
  possibleIxIy;

//  max ix is text[glob.iy].size
  
  if(glob.ix == text[glob.iy].size) return;

     glob.ix++;
     possibleIxIy;
   
  return;
}

