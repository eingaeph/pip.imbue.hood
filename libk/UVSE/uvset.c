#include "../libk.h"
//  function uvset
void uvset(void)
{   
//  query screen for size with getCursorPosition 
    int rows, cols; /* int retval = */ getCursorPosition(&rows,&cols);
//  set struct glob variables rows, cols, umax, vmax
    glob.rows = rows; glob.cols = cols;
    glob.umax = cols -1 ; glob.vmax = rows -1 ;

    return;
 }

