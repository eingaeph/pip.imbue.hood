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
     
    possibleIxIy; possibleLine;

//  ix iy may have been changed in editAline.c
//  test whether window parameters xmin etc. must be changed, as a consquence

    int testa, testb, testc, testd, teste;

    testa = (glob.ix >= glob.xmin); testb = (glob.ix <= glob.xmax); 
    testc = (glob.iy >= glob.ymin); testd = (glob.iy <= glob.ymax);
    teste = (testa && testb && testc && testd); 

//  return if unchanged window edges are ok

    if(teste) 
    {
      possibleWindow;
      glob.cu = glob.ix - glob.xmin; 
      glob.cv = glob.iy - glob.ymin; 
    return;
    }

    assert(!testa || !testb || !testc || !testd);

//  reset the window edges, xmin etc. to be consistent with ix, iy

    if (!testa) {
                 glob.xmin = glob.ix; 
                 glob.xmax = glob.xmin + glob.cols - 1;
                }
    if (!testb) {
                 glob.xmax = glob.ix; 
                 glob.xmin = glob.xmax - glob.cols + 1; 
                 if(glob.xmin < 0) glob.xmin = 0;
                }
    if (!testc) {
                 glob.ymin = glob.iy; 
                 glob.ymax = glob.ymin + glob.rows - 1; 
                 if(glob.ymax > glob.numbLines) 
                 glob.ymax=glob.numbLines-1;
                }    
    if (!testd) {
                 glob.ymax = glob.iy; 
                 glob.ymin = glob.ymax - glob.rows + 1; 
                 if(glob.ymin < 0) glob.ymin = 0;
                 }

//  after the window parm updates check again for a valid window 

    possibleIxIy; possibleLine; possibleWindow;

//  set the glob struct variables cu,cv

    glob.cu = glob.ix - glob.xmin; 
    glob.cv = glob.iy - glob.ymin;

//  hopefully this was successful and a return is appropriate

    possibleWindow;
    testa = (glob.ix >= glob.xmin); testb = (glob.ix <= glob.xmax); 
    testc = (glob.iy >= glob.ymin); testd = (glob.iy <= glob.ymax);
    teste = (testa && testb && testc && testd); 
    if(testa && testb && testc && testd) return;

//  return was not executed
//  write an error massage and terminate execution

    die("logic error in setWindow");

}
