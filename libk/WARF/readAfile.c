#include "../libk.h"

int readAfile(char *filename)
{
    fp = fopen(filename,"r");
    if(fp == NULL) {return 0;}
    int numb; int retval; int lastline;

    line.count = 0;
    for (numb = 0 ; numb < 200; numb++) 
    {
    retval=readAline(); 
    if (retval == -1) {break;}
    lastline = line.count;
    }
    if (fp != NULL) fclose(fp); else exit(1);
    return lastline;
}
