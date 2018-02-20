
//            implement scrolling
// setWindow  Set Boundary Parameters for display window
//            

void setWindow(void)
{

    int ix,iy;                 /* insertion point, text coordinates */

    int xmin,xmax,ymin,ymax;   /* window edges in text coordinates      */ 
    int umin,umax,vmin,vmax;   /* window edges in screen coordinates    */

    int lastline;              /* last line (max iy) in text            */

    int cu,cv;                 /* cursor position in screen coordinates */

    ix = global.ix;
    iy = global.iy;

    xmin = global.xmin;
    xmax = global.xmax;
    ymin = global.ymin;
    ymax = global.ymax;

    int ysize; if (lastline < 20) ysize = lastline;
               else               ysize = 20;

    if (ix > xmax)  {xmax = ix; xmin = xmax - 79;}
    if (ix < xmin)  {xmin = ix; xmax = xmin + 79;}
    if (iy > ymax)  {
                     ymax = iy;    ymin = ymax - ysize;
                     if (ymin < 0) ymin = 0; 
                    }
    writeToScreen("ix = ");writeDigit(ix,1);writeToScreen("\n\r");
    writeToScreen("iy = ");writeDigit(iy,1);writeToScreen("\n\r");
    writeToScreen("ymax = ");writeDigit(ymax,1);writeToScreen("\n\r");
    writeToScreen("ymin = ");writeDigit(ymin,1);writeToScreen("\n\r");
    writeToScreen("xmax = ");writeDigit(xmax,1);writeToScreen("\n\r");
    writeToScreen("xmin = ");writeDigit(xmin,1);writeToScreen("\n\r");

    global.xmin = xmin;
    global.xmax = xmax;
    global.ymin = ymin;
    global.ymax = ymax;

    global.cu = global.ix - global.xmin;
    global.cv = global.iy - global.ymin;


    int testa = inAline(global.ix,global.iy);
    int testb = inWindow(global.ix,global.iy);

    if (!testa) die("testa:exiting in setWindow.c");
    if (!testb) die("testb:exiting in setWindow.c");

}
