#include "../libk.h"

// function setWindow.c 
// given  struct *** text containing input file in line format
//        ix,iy  *** insertion point
// previous window xmin, xmax, ymin ymax 
// return window   xmin, xmax, ymin, ymax 

void setWindow(void)
{
    static int jx = 0, jy = 0;

    int rows, cols, retval;

    enableRawMode();
    int lena  = strlen(CursorToMaxForwardMaxDown);
    if (write(STDOUT_FILENO, CursorToMaxForwardMaxDown,lena) != lena) exit(-1);
    retval = getCursorPosition(STDIN_FILENO,STDOUT_FILENO,&rows,&cols);
    disableRawMode();


    printf("retval = %d\n",retval);
    printf("rows   = %d\n",rows);
    printf("cols   = %d\n",cols);
//  Place  Cursor Position	<ESC>[{ROW};{COLUMN}f
    write(STDOUT_FILENO,"\x1b[50;168f",9);
    exit(0);

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
