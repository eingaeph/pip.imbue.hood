#include "../libk.h"

void disableRawMode() 
{
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
    exit(0);
}
