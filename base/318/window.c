void window(int xmin, int xmax, int ymin, int ymax)
{

    writeToScreen(CursorHide);
    writeToScreen(ClearScreen);
    writeToScreen(CursorToTopLeft);

    int y; int count = 0;

/*** draw the window ***/

    for (y = ymin; y <= ymax; y++) 
   {
      if (y > global.lastline) break;
      if (text[y].row == NULL) wts("\n\r");
      else 
        {
         count = count + winOut(y, xmin, xmax);
         write(STDOUT_FILENO,"\n\r",2);
        }
   }

/*** place the cursor ***/

    writeToScreen(CursorToTopLeft);
    int no; 
    for ( no = 0; no < global.cu ; no ++ ) writeToScreen(CursorForward);
    for ( no = 0; no < global.cv ; no ++ ) writeToScreen(CursorDown);
    writeToScreen(CursorDisplay);
}
