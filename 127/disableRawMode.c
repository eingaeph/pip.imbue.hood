/*** set terminal characteristics ***/

#include <unistd.h>
#include <termios.h>
//#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "globvars.h"
#include "proto.h"


void disableRawMode() {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
    die("tcsetattr");
}



