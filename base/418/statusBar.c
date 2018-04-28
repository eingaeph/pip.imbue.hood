

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

  delay();wts(CursorToBeginingOfLine);
          wts(ClearCurrentLine); 
          wts("Status Line        "); 
  exit(1);
  die("temporary certain death at this point\n\r");

}
