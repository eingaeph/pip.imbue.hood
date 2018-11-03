// pageDown.c

#include "../libk.h"

int pageDown(void)
{
// delta = ymax - ymin 

  int delta = glob.rows -1;

// default action

   glob.ymax = glob.ymax + delta;
   glob.ymin = glob.ymin + delta;
   glob.iy = glob.ymin; glob.ix = 0;

// edge cases 

   if(glob.ymax >=  glob.numbLines) 
     {
      glob.ymax = glob.numbLines -1;
      glob.ymin = glob.ymax - delta;
      glob.ix = 0;
      glob.iy = glob.ymin;
     }
  
  if(glob.ymin < 0) 
    {
     glob.ymin = 0; 
     glob.iy = 0;
     glob.ix = 0;
    }

  possibleIxIy;
  int testy = glob.iy; testy = testy; possibleLine;

  return 0;

}

