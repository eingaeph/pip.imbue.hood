#include "../libk.h"

void arrow_right(void)
{
  possibleIxIy;
  printf("ix = %d  iy =  %d  size = %d\n\r",glob.ix,text[glob.iy].size);

//  max ix is text[glob.iy].size
  
  if(glob.ix == text[glob.iy].size) return;

     glob.ix++;
     possibleIxIy;
   
  printf("ix = %d  iy =  %d\n\r",glob.ix,glob.iy);
  int iw = 4234567; waiter(iw); // iw = 1234567;
  return;
}

