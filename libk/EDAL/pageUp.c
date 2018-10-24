#include "../libk.h"

int pageUp(void)
{

// delta = ymax - ymin 

   int delta = 24;

   possibleIxIy;

// default action

   glob.ymax = glob.ymax - delta;
   glob.ymin = glob.ymin - delta;
   glob.iy = glob.ymin; glob.ix = 0;

// edge cases 

  if(glob.ymin < 0) 
    {
     glob.ymin = 0; glob.ymax = glob.ymin + delta;
     glob.iy = 0;
     glob.ix = 0;
    }

   if(glob.ymax > glob.numbLines) glob.ymax = glob.numbLines;

                         possibleIxIy;
  int testy = glob.iy; testy = testy; possibleLine;

  return 0;

}

