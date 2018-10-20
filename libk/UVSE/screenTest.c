#include "../libk.h"
//  function screenTest
void screenTest(void)
{ 
//  retrieve Screen rows and columns from struct glob
    int rows, cols; rows = glob.rows; cols = glob.cols;
//  Move Screen Cursor to Top Left, Then Clear Screen
    printf("%s", CursorToTopLeft ClearScreen );fflush(stdout);
//  Print the Screen Header
    printf("Top of Screen: rows = %d cols = %d\n\r", rows,cols);fflush(stdout);

    int count;
//  Print Left Column Tildes to Screen, leaving screen last line clear
    for (count = 2; count < rows; count ++)
        {printf("%s", TildeReturnNewline); fflush(stdout);}
//  Prnt Screen Last Line 
    printf("%s","Bottom of Screen         "); fflush(stdout);

//  Place Cursor Position with	<ESC>[{ROW};{COLUMN}f

    printf ("\x1b[%d;%df%s", 5,5,"Hello World"); fflush(stdout);
    
//  Move Screen Cursor to Second Line, First Column 
    printf("\x1b[%d;%df",2,1); fflush(stdout);

    return; 
 }
