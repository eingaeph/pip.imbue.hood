#include "../allib.h"

// #include alvar.h   

#include "/data.base/product/libk/UVSE/UVSE.h"
#include "/data.base/product/libk/UVSE/VT100.h"


void disableRawMode() 
{
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
    exit(0);
}
