#include "../libk.h"

int arrow_up(void)
{

  int iy = glob.iy; 
  int ix = glob.ix;

  iy--; if(iy < 0 ) iy = 0;

  int size = text[iy].size;
  if (size < ix + 1 )  ix = size - 1;
  if (ix < 0 ) ix = 0;

//store the insertion point 

  glob.ix   = ix;
  glob.iy   = iy;

  return 0;

}

