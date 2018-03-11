/* edit entire text buffer */

#include <unistd.h>
#include <termios.h>
//include <string.h>
//#include <stdlib.h>
#include <stdio.h>
#include "globvars.h"
#include "proto.h"
void etxt(int maxndx)
{
    write(1,"\n",1);

    int i;
    for (i = 0; i < maxndx + 1; i++)
      {
       write(1,"text[",5);
       char buf[7];
       snprintf(buf,3,"%2d",i);
       write(1,buf,2);
       write(1,"].row: ",7);
       write(1,text[i].row,text[i].size); 
       write(1,"\n\r",2);
      } 
    return;
}

