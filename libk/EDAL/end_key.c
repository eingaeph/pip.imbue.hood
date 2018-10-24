#include "../libk.h"

int end_key(void)
{
  possibleIxIy;
//  wts("size      = "); writeDigit(text[global.iy].size,1);wts("       \n\r");   
  if (text[global.iy].size == 0) 
     {global.ix = 0; return 0;} 


//  wts("global.iy = "); writeDigit(global.iy,1);wts("       \n\r");
//  wts("global.ix = "); writeDigit(global.ix,1);wts("       \n\r");
//  wts("size      = "); writeDigit(text[global.iy].size,1);wts("       \n\r");  
  global.ix = text[global.iy].size - 1; 
  possibleIxIy;
//  wts("global.ix = "); writeDigit(global.ix,1);wts("       \n\r");
//  die("dying in end_key.c");
  return 0;

}
