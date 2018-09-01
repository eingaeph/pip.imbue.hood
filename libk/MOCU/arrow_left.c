// set insertion point on receiving <arrow_left>

#include "../WARF/WARF.h"
#include "EDAL.h"

void arrow_left(void)
{
  possibleIxIy;
  if(glob.ix == 0) return;
     glob.ix--;
}
