// test.FIND

#include "../libk.h"

void moda(int retval)
{

    setWindow();

    headwind();
    wind(glob.xmin,glob.xmax, glob.ymin, glob.ymax, glob.numbLines);
    tailwind();

    editAline(retval, glob.iy); 

    return;
}
