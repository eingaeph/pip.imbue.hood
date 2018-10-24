// set insertion point on receiving <arrow_down>

#include "../libk.h"

int arrow_down(void)
{

  int iy = glob.iy; 
  int ix = glob.ix;
  int numbLines = glob.numbLines;

  iy++; if(iy > numbLines - 1 ) iy = numbLines - 1;

  int size = text[iy].size;
  if (size < ix + 1 )  ix = size - 1;
  if (size == 0) ix = 0;

//store the insertion point 

  glob.ix   = ix;
  glob.iy   = iy;
  possibleIxIy;

  return 0;

}

