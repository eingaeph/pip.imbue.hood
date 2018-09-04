#include "../libk.h"

// given  text, ix,iy, numblines, xmin, ymin
// given previous window xmin xmax ymin ymax
//   set cursor position cu, cv
//   return xmin, xmax, ymin, ymax 
//
// check for possibleWindow before returning
//
// possibleLine
//    assert(       ((text[testy].row == NULL) &&       \
//                   (text[testy].size == 0  ))         \
//             ||                                       \
//                  ((text[testy].row != NULL) &&       \
//                   (text[testy].size >  0  ))         \
//           );
//
// possibleIxIy
//   0<=ix<=text[iy].size-1
//   0<=iy<=numblines
// 
// window u = 0,.....,cols-1
//        v = 0,.....,rows-1
// 
// four corner possible test results
// four edge non corner possible test results
//
// the corner cases do not require separate treatment
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
    int* numblines.

    xmin =&arg2.xmin; xmax = &arg2.xmax; ymin = &arg2.ymin; ymax= &arg2.ymax;
    ix = &glob.ix; iy = &glob.iy; numblines =  &glob.numblines
    cu = &arg2.cu; cv = &arg2.cv;

    possibleLine; possibleIxIy;

    int testa, testb, testc, testd, teste;
    testa = (*ix >= *xmin);
    testb = (*ix <= *xmax);
    testc = (*iy >= *ymin);
    testd = (*iy <= *ymax);
    teste = testa && testb && testc && testd;

    if (teste) {
                *cu = *ix - *xmin; 
                *cv = *iy - *ymin;
                print("\x1b[%d;%df",*cv,*cu);
                return;
               }

//  adjust xmin, xmax

    asset(!testa || !testb || !testc || !testd);

    if(!testa) {*xmin = *ix; *xmax = *xmin + cols - 1;}
    if(!testb) {*xmax = *ix; *xmin = *xmax - cols + 1;}

//  adjust ymin, ymax

    if (!testc) {*ymin = *iy; *ymax = *ymin + rows - 1;}
    if (!testd) {*ymax = *iy; *ymin = *ymax - rows + 1;}

// final test : possibleWindow

//   xmin<=ix<=xmax 
//   ymin<=iy<=ymax

    testa = (*ix >= *xmin);
    testb = (*ix <= *xmax);
    testc = (*iy >= *ymin);
    testd = (*iy <= *ymax);
    teste = testa && testb && testc && testd;
    assert(teste);

    assert( xmax - xmin <= cols -1);
    assett( ymax - ymin <= rows -1);

    assert( xmin >= 0); assert(xmax > xmin);
    assert( ymin >= 0);
    assert(ymax <= numblines -1):

    return;
}
