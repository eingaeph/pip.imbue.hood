
//            implement scrolling
// setWindow  Set Boundary Parameters for display window
//            

void setWindow(void)
{

//    int ix,iy;                 /* insertion point, text coordinates */
//    int lastline;              /* last line (max iy) in text            */

//    int xmin,xmax,ymin,ymax;   /* window edges in text coordinates      */ 
//    int umin,umax,vmin,vmax;   /* window edges in screen coordinates    */

//    int cu,cv;                 /* cursor position in screen coordinates */

    possibleIxIy;

    int ysize; if (global.lastline < 20) ysize = global.lastline;
               else                      ysize = 20;

    if (global.ix > global.xmax)  {global.xmax = global.ix; global.xmin = global.xmax - 79;}
    if (global.ix < global.xmin)  {global.xmin = global.ix; global.xmax = global.xmin + 79;}
    if (global.iy > global.ymax)  
                  {
                       global.ymax = global.iy;    
                       global.ymin = global.ymax - ysize;
                   if (global.ymin < 0) global.ymin = 0; 
                  }

    global.cu = global.ix - global.xmin;
    global.cv = global.iy - global.ymin;

    possibleLine;

}
