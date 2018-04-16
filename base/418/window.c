void window(int xmin, int xmax, int ymin, int ymax)
{

    writeToScreen(CursorHide);
    writeToScreen(ClearScreen);
    writeToScreen(CursorToTopLeft);

    int y; int count = 0;

    testScreen;

    for (y = ymin; y <= ymax; y++) 
   {
     if (y > global.lastline) break;

     assert(!(text[y].size > 0 && text[y].row == NULL));
     if(text[y].row == NULL) {write (STDOUT_FILENO,"\n\r",2);
                              continue; }

    char *s = xmin + text[y].row; 

    int no;
    for ( no = 0; no + xmin <= xmax; no++)
    {
    if (no==text[y].size) {break;};
    if (*s == '\r')       {break;};
    if (*s == '\n')       {break;};
    write(STDOUT_FILENO,s,1); s++; count++;
    }
    write(STDOUT_FILENO,"\n\r",2);
   }

//    wts("placing the cursor \n\r");

    writeToScreen(CursorToTopLeft);
    int no; 
    for ( no = 0; no < global.cu ; no ++ ) writeToScreen(CursorForward);
    for ( no = 0; no < global.cv ; no ++ ) writeToScreen(CursorDown);
    writeToScreen(CursorDisplay);

}
