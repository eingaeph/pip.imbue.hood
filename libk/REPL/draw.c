// draw.c
//    clear the screen and draw the window

#include "../libk.h"

void draw(void)
{
//  Clear the screen an place the cursor at the top left

    printf(ClearScreen); fflush(stdout); 
    int cu = 0; int cv = 0;
    printf("\x1b[%d;%df",cv,cu); fflush(stdout);
    printf("xmin = %d xmax = %d\n\r", glob.xmin,glob.xmax); 
    printf("ymin = %d ymax = %d\n\r", glob.ymin,glob.ymax);
    printf("numblines = %d\n\r",glob.numbLines);
    exit(0);

//  draw the window beginning at the cursor

    wind(glob.xmin,glob.xmax, glob.ymin, glob.ymax, glob.numbLines);
    return;
}
