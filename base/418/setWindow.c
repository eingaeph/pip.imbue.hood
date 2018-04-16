
// implement scrolling
// Set Boundary Parameters xmin, ymin... for display window
//            

void setWindow(void)
{

//    lastline is last line (max iy) in text coordinates

//    int xmin,xmax,ymin,ymax;   /* window edges in text coordinates      */ 
//    int umin,umax,vmin,vmax;   /* window edges in screen coordinates    */

//    int cu,cv;                 /* cursor position in screen coordinates */

    possibleIxIy;
    int testa, testb, testc, testd;

#define tests testa = (global.ymax >= global.iy);      \
              testb = (global.ymin <= global.iy);      \
              testc = (global.xmax >= global.ix);      \
              testd = (global.xmin <= global.ix);      
    tests;

    if (testa && testb && testc && testd) 
      {
       global.cu = global.ix - global.xmin;
       global.cv = global.iy - global.ymin;
       return;
      }

    assert(global.xmin >= 0); assert(global.xmin < global.xmax);
    assert(global.ymin >= 0); assert(global.ymin < global.ymax);

//    change one or more of xmin, xmax

    if (global.ix > global.xmax)  
      { global.xmax = global.ix; global.xmin = global.xmax - 79;}

    if (global.ix < global.xmin)  
      { global.xmin = global.ix; global.xmax = global.xmin + 79;}

    tests;

    if (testa && testb && testc && testd) 
      {
       global.cu = global.ix - global.xmin;
       global.cv = global.iy - global.ymin;
       return;
      }

    
    assert (global.iy <= global.lastline); assert (global.iy >= 0);

//    change one or both of ymin, ymax

    int ysize; if (global.lastline < 20) ysize = global.lastline;
               else                      ysize = 20;

    if (global.iy > global.ymax)  
                  {
                       global.ymax = global.iy;    
                       global.ymin = global.ymax - ysize;
                   if (global.ymin < 0) global.ymin = 0; 
                  }

    if (global.iy < global.ymin)
      {
        global.ymin = global.iy;
        global.ymax = global.ymin + ysize;
        if (global.ymax > global.lastline) global.ymax = global.lastline;
      }

    tests; 

    if (testa && testb && testc && testd) 
      {
       global.cu = global.ix - global.xmin;
       global.cv = global.iy - global.ymin;
       return;
      }

#undef tests

    die("consistency failure in setWindow.c");
}
