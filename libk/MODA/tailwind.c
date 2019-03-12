#include "../libk.h"

void tailwind(void)
{

//  Place the cursor in its final position

    int cu = glob.cu; int cv = glob.cv;
    assert(cu == glob.ix - glob.xmin);
    assert(cv == glob.iy - glob.ymin);
    enableRawMode(); printf("\x1b[%d;%df",(cv+1),(cu+1)); fflush(stdout); disableRawMode();

}
