
/* write a single digit to the screen */

#include <unistd.h>
#include <termios.h>
//#include <string.h>
//#include <stdlib.h>
#include <stdio.h>
#include "globvars.h"
#include "proto.h"

void writeDigit(int digit)
{
//char buf[] = "abcdefghijklmnopqrstuvwxyz";
  char buf[] = "                          ";
   snprintf(buf,4,"%d",digit);
   write(STDOUT_FILENO,buf,4);
   return;
}
