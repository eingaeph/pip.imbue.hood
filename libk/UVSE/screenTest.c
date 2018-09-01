#include "../libk.h"

void screenTest(void)
{ 
    int rows, cols; rows = glob.rows; cols = glob.cols;

    printf("%s", CursorToTopLeft ClearScreen );fflush(stdout);
    printf("Top of Screen: rows = %d cols = %d\n\r", rows,cols);fflush(stdout);

    int count;
    for (count = 2; count < rows; count ++)
        {printf("%s", TildeReturnNewline); fflush(stdout);}

    printf("%s","Bottom of Screen         "); fflush(stdout);

//  Force Cursor Position with	<ESC>[{ROW};{COLUMN}f

    printf ("\x1b[%d;%df%s", 5,5,"Hello World"); fflush(stdout);
    
//
    printf("\x1b[%d;%df",2,1); fflush(stdout);

    return; 
 }
