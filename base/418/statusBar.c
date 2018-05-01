

void statusBar(void)
{

  int nrows, ncols;
  getWindowSize(STDIN_FILENO,STDOUT_FILENO,&nrows,&ncols);

//  wts("the number of rows = ");writeDigit(nrows,1);wts("\n\r");
//  wts("the number of cols = ");writeDigit(ncols,1);

  wts(CursorToTopLeft);wts(ClearScreen);
  wts("     Welcome");
  wts(CursorToTopLeft);


  int irow; for (irow = 0; irow < nrows; irow++) 
    {wts("~");if (irow + 1 < nrows) wts("\n\r");}

  wts(CursorToBeginingOfLine); wts(ClearCurrentLine); 

//    wts("placing the cursor \n\r");

  writeToScreen(CursorHide); writeToScreen(CursorToTopLeft);
  int no; 
  for ( no = 0; no < 0 ; no ++ )     writeToScreen(CursorForward);
  for ( no = 0; no < nrows ; no ++ ) writeToScreen(CursorDown);
  writeToScreen(CursorDisplay);
  wts("Status Line        "); 

}
