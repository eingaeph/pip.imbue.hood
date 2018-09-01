#include "../libk.h"
 
//  query screen for size
//  clear display 
//  display top of screen line (line 1 is top of screen)
//  display tildes along left sign of screen
//  display bottom of screen line (line rows is bottom of screen) 

void uvset(void)
{   

    /* Place Cursor */ int lena = strlen( CursorToMaxForwardMaxDown );
    write(STDOUT_FILENO, CursorToMaxForwardMaxDown, lena );
    int rows, cols; /* int retval = */ getCursorPosition(&rows,&cols);
    glob.rows = rows; glob.cols = cols;
    glob.umax = cols -1 ; glob.vmax = rows -1 ;

    return;
 }

