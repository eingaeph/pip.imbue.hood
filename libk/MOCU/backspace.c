
// set insertion point on receiving <backspace>

#include "../WARF/WARF.h"
#include "EDAL.h"

void backspace(void)
{
  if (glob.ix > 0) glob.ix--; //else glob.ix = 0; 
  possibleIxIy;  
}
