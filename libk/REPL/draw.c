// draw.c
//    clear the screen and draw the window

#include "../libk.h"

void draw(void)
{
//  Clear the screen an place the cursor at the top left

    printf(ClearScreen); fflush(stdout); 
    int cu = 1; int cv = 1;
    printf("\x1b[%d;%df",cv,cu); fflush(stdout);
 
    printf("here is where the writing starts");
//  draw the window beginning at the cursor
  
    wind(glob.xmin,glob.xmax, glob.ymin, glob.ymax, glob.numbLines);
 int iw = 3234567; waiter(iw); // iw = 1234567;

    exit(0);
    return;
}
