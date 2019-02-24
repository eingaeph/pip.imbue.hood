#include "../libk.h"

void callWind(int cu, int cv)
{
    printf("in callWind\n"); // exit(0);
    setWindow();

//  Clear the screen; temporarily place the cursor at the top left

    enableRawMode(); printf(ClearScreen); fflush(stdout); disableRawMode();
    int tcu = 1; int tcv = 1;
    enableRawMode(); printf("\x1b[%d;%df",tcv,tcu); fflush(stdout); disableRawMode();

//  draw the window when changing between modes

    rend(glob.xmin,glob.xmax, glob.ymin, glob.ymax, glob.numbLines);

//  Place the cursor in its final position

    cu++; cv++;
    enableRawMode(); printf("\x1b[%d;%df",cv,cu); fflush(stdout); disableRawMode();

}
