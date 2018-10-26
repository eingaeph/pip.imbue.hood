// setWindow.c
#include "../libk.h"

// given    struct *** text containing input file in line format
//          ix,iy  *** insertion point in text coordinates
//          rows, cols *** screenszie
//          numblines *** number of lines in struct text
//          xmin, xmax, ymin, ymax *** previous window edges in text coordinates 

// return   xmin, xmax, ymin, ymax *** updated window edges
//          cu, cv *** cursor position in screen coordinates 

// four edge non corner possible test results
//
// the corner cases do not require separate treatment
//   x test, then xmin, xmax set
//   y test, then ymin, ymax set
//   set cursor coordinates 
//   assert possibleWindow and return

void setWindow(void)
{
 
//  initialize the variables used by setWindow.c 

    int ix = glob.ix; int iy = glob.iy; 
    int xmin = glob.xmin ; int xmax = glob.xmax ;
    int ymin = glob.ymin ; int ymax = glob.ymax ;
    int rows = glob.rows ; int cols = glob.cols ;
    int numbLines = glob.numbLines;
    int cu, cv; //these will be initialized later

//  check the variables just initialized for consistency
    
    possibleIxIy; int testy = iy; testy=testy; possibleLine;
    assert( xmax - xmin <= cols - 1);
    assert( ymax - ymin <= rows - 1); 

//  ix iy may have been changed in editAline.c
//  test whether window parameters xmin etc. must be changed, as a consquence

    int testa, testb, testc, testd, teste;

    testa = (ix >= xmin); testb = (ix <= xmax); 
    testc = (iy >= ymin); testd = (iy <= ymax);
    teste = (testa && testb && testc && testd); 
    assert (iy <= numbLines - 1);

//  return if unchanged window edges are ok

    if(teste) 
    {
    cu = glob.ix - glob.xmin; glob.cu = cu;
    cv = glob.iy - glob.ymin; glob.cv = cv;
    enableRawMode();
//  move cursort to insertion point
    printf("\x1b[%d;%df",cu,cv); fflush(stdout);
    disableRawMode();
    return;
    }

    assert(!testa && !testb && !testc && !testd);

//  reset the window edges, xmin etc. to be consistent with ix, iy

    if (!testa) {xmin = ix; xmax = xmin + rows - 1;}
    if (!testb) {xmax = ix; xmin = xmax - rows + 1; if(xmin < 0) xmin = 0;}
    if (!testc) {ymin = iy; ymax = ymin + cols - 1; if(ymax > numbLines) ymax=numbLines-1;}    
    if (!testd) {ymax = iy; ymin = ymax - cols + 1; if(ymin < 0) ymin = 0;}

//  after the window parm updates check again for a valid window 

    possibleIxIy; testy = iy; testy = testy; possibleLine;
    assert( xmax - xmin <= cols - 1);
    assert( ymax - ymin <= rows - 1); 

    testa = (ix >= xmin); testb = (ix <= xmax);
    testc = (iy >= ymin); testd = (iy <= ymax);

//  set the glob struct variables cu,cv,xmin,xmax,ymin,ymax

    glob.xmin = xmin ; glob.xmax = xmax;
    glob.ymin = ymin ; glob.ymax = ymax;
    cu = glob.ix - glob.xmin; glob.cu = cu;
    cv = glob.iy - glob.ymin; glob.cv = cv;

//  move cursor to cu,cv (screen coordinates)

    enableRawMode();
    printf("\x1b[%d;%df",cu,cv); fflush(stdout);
    disableRawMode();

//  hopefully this was successful and a return is appropriate

    if (testa && testb && testc && testd ) return; 

//  return was not executed
//  write an error massage and terminate execution

    die("logic error in setWindow");

}
