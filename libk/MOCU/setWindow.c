#include "../libk.h"

// given  text, ix,iy, numblines
// given previous window xmin xmax ymin ymax
//   set cursor position cu, cv
//   return xmin, xmax, ymin, ymax 
//
// possibleLine
//
// possibleIxIy
//   0<=ix<=text[iy].size-1
//   0<=iy<=numblines
// 
// test inWindow
//   xmin<=ix<=xmax 
//   ymin<=iy<=ymax
// return immediately
//
// window u = 0,...,cols-1
//        v = 0,.....rows-1
// 
// four corner possible test results
// four edge non corner possible test results
//
// the corner cases do not require separate treatemnt
// except that x and y adjustments must happen each time
//   x test, then xmin, xmax set
//   y test, then ymin, ymax set
//   set cursor wind 
// assert possibleWindow and return

void setWindow(void)
{
    int* xmin; int* xmax; int* ymin; int* ymax; 
    int* ix; int* iy;
    int* cu; int* cv;

    xmin =&arg2.xmin; xmax = &arg2.xmax; ymin = &arg2.ymin; ymax= &arg2.ymax;
    ix = &glob.ix; iy = &glob.iy;
    cu = &arg2.cu; cv = &arg2.cv;

    possibleLine; possibleIxIy;
    testa = (*ix >= *xmin);
    testb = (*ix <= *xmax);
    testc = (*iy >= *ymin);
    testd = (*iy <= *ymax);
    teste = testa && testb && testc && testd;

    if (teste) 
      {
//Set Cursor Position	<ESC>[{ROW};{COLUMN}f
    *cu = *ix + 1; *cv = *iy + 1
    print("\x1b[%d;%df",*cv,*cu);
    exit(0);
       {
    int ix = glob.ix; int iy = glob.iy; 
    possibleIxIy; int testy = iy; possibleLine;

    if ((ix == jx) && (iy = jy)) return;

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
