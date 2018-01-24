
/* delete a line in the text buffer */

//#include <unistd.h>
#include <termios.h>
//#include <errno.h>
#include <stdlib.h>
#include "globvars.h"
#include "proto.h"

int deleteAline(int omit,int maxndx)
{
    int newlen = maxndx + 1 - 1;
    slot *new  = (slot *)malloc(newlen*sizeof(slot));

    slot *old = text; 

    int i,j,k; i = 0; j = 0; k = 0;
    for (i = 0 ; i < maxndx + 1 ; i++) 
      {if (i != omit) {new[j] = old[k]; j++; k++;}
       else           {                      k++;}
      }

    free(text[omit].row);
    free(text); text = new;  

    maxndx--;
    return maxndx;
}
