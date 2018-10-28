// draw.c
//    clear the screen and draw the window

void draw(void)
{
//  Clear the screen an place the cursor at the top left

    enableRawMode(); printf(ClearScreen); fflush(stdout); disableRawMode();
    int cu = 0; int cv = 0;
    enableRawMode(); printf("\x1b[%d;%df",cv,cu); fflush(stdout); disableRawMode();

//  draw the window beginning at the cursor

    wind(glob.xmin,glob.xmax, glob.ymin, glob.ymax, glob.numbLines);
    return;
}
