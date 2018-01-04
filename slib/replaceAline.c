
/*function replaceAline */

// makes one call to malloc for replacement text  
// plus  one call to free text[nsrt].row (the replaced element)
// plus  one call to free text (the entire replaced document)

//#include <unistd.h>
#include <termios.h>
//#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "globvars.h"
#include "proto.h"

int replaceAline(int nsrt,int maxndx)
{
    int newlen = maxndx + 1 + 0;
    slot *new  = (slot *)malloc(newlen*sizeof(slot));

    slot newline;
    char *ptr = "Hello World! I am a replacement line.\n";
    newline.size = strlen(ptr)-1;
    char *qtr = (char *)malloc(strlen(ptr)-1);
    memcpy(qtr,ptr,strlen(ptr)); 
    newline.row = qtr;

    slot *old = text; 

    int i,j,k; i = 0; j = 0; k = 0;
    for (i = 0 ; i < maxndx + 1 ; i++) 
      {if (i != nsrt) {new[j] = old[k]; j++; k++;}
       else           {new[j] = newline;j++; k++;}
      }

    free(text[nsrt].row);
    free(text); text = new;  

    return maxndx;
}
