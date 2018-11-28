#include "../libk.h"

void callWind(int cu, int cv)
{
    setWindow();

//  Clear the screen an place the cursor at the top left

    enableRawMode(); printf(ClearScreen); fflush(stdout); disableRawMode();
    cu++; cv++;
    enableRawMode(); printf("\x1b[%d;%df",cv,cu); fflush(stdout); disableRawMode();

//  draw the window when changing between modes

    wind(glob.xmin,glob.xmax, glob.ymin, glob.ymax, glob.numbLines);

}
