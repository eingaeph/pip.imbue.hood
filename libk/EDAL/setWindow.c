#include "../libk.h"

// function setWindow.c 
// given  struct *** text containing input file in line format
//        ix,iy  *** insertion point
// screensize rows, cols
// previous window xmin, xmax, ymin ymax 
// return window   xmin, xmax, ymin, ymax 

void setWindow(void)
{
 
    int ix = glob.ix; int iy = glob.iy; 
    int xmin = glob.xmin ; int xmax = glob.xmax ;
    int ymin = glob.ymin ; int ymin = glob.ymax ;
    int rows = glob.rows ; int cols = glob.cols ;
    int numblines = glob.numblines;

    possibleIxIy; int testy = iy; possibleLine;
    assert( xmax - xmin <= cols - 1);
    assert( ymax - ymin <= rows - 1); 

//  ix iy may have changed
//  test whether window parameters must be changed

    testa = (ix >= xmin);
    testb = (ix <= xmax);
    testc = (iy >= ymin);
    testd = (iy <= ymax);
    assert (iy <= numblines - 1);

    if(testa && testb && testc && testd ) return; 

//  here setWindow attempts to reset the window edges, xmin etc.

    if (!testa) {xmin = ix; xmax = xmin + rows - 1;}
    if (!testb) {xmax = ix; xmin = xmax - rows + 1, if(xmin < 0) xmin = 0;}
    if (!testc) {ymin = iy; ymax = ymin + cols - 1; if(ymax > numblines) ymax=numblines-1;}    
    if (!testd) {ymax = iy; ymin = ymax - cols + 1; if(ymin < 0) ymin = 0;}

    glob.cu = glob.ix - glob.xmin;
    glob.cv = glob.iy - glob.ymin;

//  after the above updates check for a valid window again
    possibleIxIy; testy = iy; possibleLine;
    assert( xmax - xmin <= cols - 1);
    assert( ymax - ymin <= rows - 1); 


    testy = glob.iy; possibleLine;

    assert( ymax - ymin <= rows - 1); 

//  ix iy may have changed
//  test whether window parameters must be changed
    testa = (ix >= xmin);
    testb = (ix <= xmax);
    testc = (iy >= ymin);
    testd = (iy <= ymax);
    assert (iy <= numblines - 1);

    if(testa && testb && testc && testd ) return; 

}
