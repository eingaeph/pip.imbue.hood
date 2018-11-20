// set insertion point on receiving <arrow_left>

#include "../libk.h"

void arrow_left(void)
{
  possibleIxIy;
  if (glob.ix == 0 && glob.iy == 0 ) 
    {possibleIxIy; return;}
  if (glob.ix == 0 && glob.iy >= 1 ) 
    {
     glob.iy--;
     glob.ix = text[glob.iy].size - 1;
     if(glob.ix < 0) glob.ix = 0;
     possibleIxIy; return;
    }

  glob.ix--; possibleIxIy; return;
}
