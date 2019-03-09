#include "../libk.h"

int readAfile(char *filename)
{
    fp = fopen(filename,"r");
    if(fp == NULL) {return 0;}
    int numb; int lastline;

    line.count = 0;
    for (numb = 0 ; numb < 200; numb++) 
    {
    int retval=readAline(); 
    if (retval == -1) {break;}
    lastline = line.count;
    }
    if (fp != NULL) fclose(fp); else exit(1);

    for(int i = 0; i < lastline; i++)
      {
        if(text[i].size == 0) assert(text[i].row == NULL);
      }

    return lastline;
}
