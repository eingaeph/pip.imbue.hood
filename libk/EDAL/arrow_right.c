#include "../libk.h"

void arrow_right(void)
{
  possibleIxIy;

//  the maximum allowable ix is text[iy].size

//  check for end of document

  if(glob.ix == text[glob.iy].size && glob.iy == glob.numbLines - 1 ) return;

//  arrow right at end of line moves to the beginning of the next line
 
  if(glob.ix == text[glob.iy].size) 
    {glob.ix = 0; glob.iy++; possibleIxIy; return;}

//  not at end of line, the default case

   glob.ix++; possibleIxIy; return;
}

