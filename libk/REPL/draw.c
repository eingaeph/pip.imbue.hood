// draw.c
//    clear the screen and draw the window

#include "../libk.h"

void draw(void)
{

//  Call setWindow to updae xmin, xmax, ymin, ymax 
//    to agree with the insertion point ix, iy

    setWindow();

//  Clear the screen an place the cursor at the top left

    printf(ClearScreen); fflush(stdout); 
    int cu = 1; int cv = 1;
    printf("\x1b[%d;%df",cv,cu); fflush(stdout);
 
//  draw the window beginning at the cursor
  
    wind(glob.xmin,glob.xmax, glob.ymin, glob.ymax, glob.numbLines);

    return;
}
