#include "../libk.h"

void headwind(void)
{
    setWindow();

//  Clear the screen; temporarily place the cursor at the top left

    enableRawMode(); printf(ClearScreen); fflush(stdout); disableRawMode();
    int tcu = 1; int tcv = 1;
    enableRawMode(); printf("\x1b[%d;%df",tcv,tcu); fflush(stdout); disableRawMode();

//  next call wind or rend

}
