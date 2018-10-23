#include "../libk.h"

// function setWindow.c 
// given  struct *** text containing input file in line format
//        ix,iy  *** insertion point
// screensize rows, cols
// previous window xmin, xmax, ymin, ymax 
// return window   xmin, xmax, ymin, ymax 

void setWindow(void)
{
 
//  initialize the variables used by 

    int ix = glob.ix; int iy = glob.iy; 
    int xmin = glob.xmin ; int xmax = glob.xmax ;
    int ymin = glob.ymin ; int ymin = glob.ymax ;
    int rows = glob.rows ; int cols = glob.cols ;
    int numblines = glob.numblines;

//  check the variables just initialized for consistency
    
    possibleIxIy; int testy = iy; possibleLine;
    assert( xmax - xmin <= cols - 1);
    assert( ymax - ymin <= rows - 1); 

//  ix iy may have been changed in edal.c
//  test whether window parameters xmin etc. must be changed, as a consquence

    testa = (ix >= xmin); testb = (ix <= xmax);
    testc = (iy >= ymin); testd = (iy <= ymax);
    assert (iy <= numblines - 1);

    if(testa && testb && testc && testd ) return; 

//  here setWindow resets the window edges, xmin etc.

    if (!testa) {xmin = ix; xmax = xmin + rows - 1;}
    if (!testb) {xmax = ix; xmin = xmax - rows + 1, if(xmin < 0) xmin = 0;}
    if (!testc) {ymin = iy; ymax = ymin + cols - 1; if(ymax > numblines) ymax=numblines-1;}    
    if (!testd) {ymax = iy; ymin = ymax - cols + 1; if(ymin < 0) ymin = 0;}

//  after the updates check again for a valid window 

    possibleIxIy; testy = iy; possibleLine;
    assert( xmax - xmin <= cols - 1);
    assert( ymax - ymin <= rows - 1); 

    testa = (ix >= xmin); testb = (ix <= xmax);
    testc = (iy >= ymin); testd = (iy <= ymax);

//  set the glob struct variables cu,cv,xmin,xmax,ymin,ymax

    glob.cu = glob.ix - glob.xmin;
    glob.cv = glob.iy - glob.ymin;
    glob.xmin = xmin ; glob.xmax = xmax;
    glob.ymin = ymin ; glob.ymax = ymax;

//  hopefully all this was a success and a return is appropiate

    if (testa && testb && testc && testd ) return; 

//  but now we write an error massage and terminate execution

    die("logic error demonstrated in setWindow");
}
