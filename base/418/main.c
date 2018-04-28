

int main(int argc, char** argv)
{

  init(argc, argv);

  int nrows, ncols;
  getWindowSize(STDIN_FILENO,STDOUT_FILENO,&nrows,&ncols);

  wts("the number of rows = ");writeDigit(nrows,1);wts("\n\r");
  wts("the number of cols = ");writeDigit(ncols,1);
  wts(CursorToTopLeft);wts(ClearScreen);


  int irow; for (irow = 0; irow < nrows; irow++) 
    {writeDigit(irow,1);if (irow + 1 < nrows) wts("\n\r");}

  delay();wts(CursorToTopLeft); exit(1);
  die("temporary certain death at this point\n\r");

  setWindow();

  window(global.xmin,global.xmax,
         global.ymin,global.ymax);

  while (1) 

   {

    int testa = 1; int retval;


    if (testa)  retval = replay();
    if (!testa) retval = ReadKey(); 

    if (retval == CTRL_Q) die("\n\n\n\n\r") ;

    int testb = (retval != CTRL_U);

    if (testb)
      {
        edal(retval, global.iy);

        setWindow();

        window(global.xmin,global.xmax,
               global.ymin,global.ymax);
      }

    else sear();
  
   }

  return 0; // this statement is never reached
}
