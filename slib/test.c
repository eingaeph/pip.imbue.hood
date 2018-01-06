//#! /usr/bin/tcc -run -L/home/ubuntu/git/repo.1/slib -l127 test.dat

// `-lxxx' Link your program with static library libxxx.a. 

#include <unistd.h>   //read,write
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h> //open,close per Kerrisk page 72
#include <fcntl.h>    //open,close per Kerrisk page 72

#include <ctype.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <termios.h>

#include "vt100.h"

/*** REAF, IO, ADAL, NCOD ***/

/*** global variables ***/

    size_t linecap;
    int nread;
    struct { int fp; int nread; } nput;

typedef struct slot
{
    ssize_t size;
    char *row;
    int count;
}   slot;

    slot line;
    slot *text;

struct termios orig_termios;

/*** function declarations used in main ***/


void enableRawMode();

void writeDigit(int digit);

char ReadKey();

int addAline(int here,int maxndx);

int deleteAline(int omit,int maxndx);

void etxt(int maxndx);

int replaceAline(int nsrt,int maxndx);

int readAline(void);

/* main (sets off the linkage chain) */ 

int main(int argc, char** argv)
{
    char* filename = argv[1];
    int numb; int retval; int lastline;

    if(argc == 1) return 0;

    write(1,argv[1],strlen(argv[1]));
    write(1,"\r\n",2);

    nput.fp = open(filename,O_RDONLY);

    line.count = 0;
    for (numb = 0 ; numb < 100; numb++) 
    {
    retval=readAline(); 
    if (nput.nread < 1) {break;}
    lastline = line.count; 
    }
    
    close(nput.fp);
    char buf[8];
    snprintf(buf,8,"%d\n",lastline);
    write(1,buf,strlen(buf));
    write(1," lines were read\n\r",17);

    int maxndx = lastline - 1; etxt(maxndx);

    maxndx = replaceAline(5,maxndx); etxt(maxndx);

    maxndx = deleteAline(7,maxndx); etxt(maxndx);

    maxndx = addAline(2,maxndx); etxt(maxndx);

/***

  enableRawMode();

  while (1) 
{
    char c = ReadKey();
    write (STDOUT_FILENO, "c = ", 4);
    writeDigit(c); 
    write (STDOUT_FILENO, "\r\n",2);
    if ( (c > 31) && (c < 127) ) 
    { write(STDOUT_FILENO, "printable character\r\n",21); }

    if ( (c > 0) && (c < 27) )
    { write(STDOUT_FILENO, "CTRL + letter\r\n",16); }
}

***/

    return 0;
 }

