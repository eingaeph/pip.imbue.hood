#include "gather.h"

int readAfile(char *filename)
{
    fp = fopen(filename,"r");
    int numb; int retval; int lastline;

    line.count = 0;
    for (numb = 0 ; numb < 20; numb++) 
    {
    retval=readAline(); 
    if (retval == -1) {break;}
    lastline = line.count;
    }
    if (fp != NULL) fclose(fp); else exit(1);
    return lastline;
}
