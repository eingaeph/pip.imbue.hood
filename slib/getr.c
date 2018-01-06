/* getline replacement */

#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <stdlib.h>
#include "globvars.h"
#include "proto.h"

int getr(char **qtr) // getline replacement
{
  char line[240];     // sets maximum linesize at three times reasonable
  char* s = &line[0]; // s and line are nearly each other's  alias
  int linesize;
  char* ptr;

  linesize = 0; s = &line[0];
  while((nput.nread = read(nput.fp,s,1))==1) 
     {if (*s != '\n') {s++; linesize++;} else break;}
   
/***
  here nread = EOF 0,ERROR 1 
       linesize is posibly zero, possibly greater than zero
***/

  if (linesize != 0) {ptr = malloc(linesize*sizeof(char));}
  if (linesize != 0) memcpy(ptr,line,linesize);
  if (linesize != 0) *qtr = ptr;
  return linesize;
}

