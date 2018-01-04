
/* delete a line from the text buffer */

//#include <unistd.h>
#include <termios.h>
//#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "globvars.h"
#include "proto.h"

int addAline(int here,int maxndx)

{
    int newlen = maxndx + 1 + 1;
    slot *new  = (slot *)malloc(newlen*sizeof(slot));

    slot newline;
    char *ptr = "Yes, I am a new line!\n";
    newline.size = strlen(ptr)-1;
    char *qtr = (char *)malloc(strlen(ptr)-1);
    memcpy(qtr,ptr,strlen(ptr)); 
    newline.row = qtr;

    slot *old = text; 

    int i,j,k; i = 0; j = 0; k = 0;
    for (i = 0 ; i < maxndx + 1 ; i++) 
      {if (i != here) {new[j] = old[k]; j++; k++;}
       else           {new[j] = old[k]; j++; k++;
                       new[j] = newline;     j++;}
      }


    free(text); text = new;  
   
    maxndx++;
    return maxndx;
}

