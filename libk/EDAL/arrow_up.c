#include "../libk.h"

int arrow_up(void)
{

  int iy = global.iy; 
  int ix = global.ix;
  int ymax = global.ymax;
  int lastline = global.lastline;


  writeToScreen("arow iy =  ");writeDigit(global.iy,1);writeToScreen("       kkk\n\r");
  writeToScreen("arow ix =  ");writeDigit(global.ix,1);writeToScreen("       kkk\n\r");

  iy--; if(iy < 0 ) iy = 0;

  int size = text[iy].size;
  if (size < ix + 1 )  ix = size - 1;
  if (ix < 0 ) ix = 0;

//store the insertion point 

  global.ix   = ix;
  global.iy   = iy;

  writeToScreen("arow iy =  ");writeDigit(global.iy,1);writeToScreen("       lll\n\r");
  writeToScreen("arow ix =  ");writeDigit(global.ix,1);writeToScreen("       lll\n\r");

  return 0;

}

