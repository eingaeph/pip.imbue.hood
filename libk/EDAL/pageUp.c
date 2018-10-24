#include "../libk.h"

int pageUp(void)
{

// delta = ymax - ymin 

   int delta = 24;

   possibleIxIy;

// default action

   global.ymax = global.ymax - delta;
   global.ymin = global.ymin - delta;
   global.iy = global.ymin; global.ix = 0;

// edge cases 

  if(global.ymin < 0) 
    {
     global.ymin = 0; global.ymax = global.ymin + delta;
     global.iy = 0;
     global.ix = 0;
    }

   if(global.ymax > global.lastline) global.ymax = global.lastline;

                         possibleIxIy;
  int testy = global.iy; possibleLine;

  return 0;

}

