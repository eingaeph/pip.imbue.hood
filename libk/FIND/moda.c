// test.FIND

#include "../libk.h"

void moda(int retval)
{
/*
//    editAline(retval, glob.iy); 
    setWindow();

//  Clear the screen an place the cursor at the top left

    enableRawMode(); printf(ClearScreen); fflush(stdout); disableRawMode();
    int cu = 0; int cv = 0;
    enableRawMode(); printf("\x1b[%d;%df",cv,cu); fflush(stdout); disableRawMode();

//  draw the window

    wind(glob.xmin,glob.xmax, glob.ymin, glob.ymax, glob.numbLines);

//  set cursor position corresponding to ix, iy

    cu = glob.cu; cv = glob.cv;
    assert(cu == glob.ix - glob.xmin);
    assert(cv == glob.iy - glob.ymin);
    enableRawMode(); printf("\x1b[%d;%df",(cv+1),(cu+1)); fflush(stdout); disableRawMode();
*/
    callWind(glob.cu,glob.cv);

    editAline(retval, glob.iy); 

    return;
}
