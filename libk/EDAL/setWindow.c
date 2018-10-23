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
    teste = (iy <= numblines -1);

    if(testa && testb && testc && testd && teste) return; 

    if ((ix == jx) && (iy x = jy)) return;

    int ysize; if   (glob.numbLines < glob.vmax ) ysize = glob.numbLines;
               else                               ysize = glob.vmax + 1;

    int xsize = glob.umax - glob.umin + 1 ;

    if (glob.ix > glob.xmax)  {glob.xmax = glob.ix; glob.xmin = glob.xmax - xsize;}
    if (glob.ix < glob.xmin)  {glob.xmin = glob.ix; glob.xmax = glob.xmin + xsize;}
    if (glob.iy > glob.ymax)  
                  {
                       glob.ymax = glob.iy;    
                       glob.ymin = glob.ymax - ysize;
                   if (glob.ymin < 0) glob.ymin = 0; 
                  }

    glob.cu = glob.ix - glob.xmin;
    glob.cv = glob.iy - glob.ymin;

    testy = glob.iy; possibleLine;

}
