#! /usr/bin/tcc -run

#include <unistd.h>   //write, read
#include <stdlib.h>   //malloc
#include <string.h>   //memcpy
#include <sys/stat.h> //open,close per Kerrisk page 72
#include <fcntl.h>    //open,close 

//  GETR.c  getline replacement
//  using multiple indirection to pass a char array 

int funy(char **qtr)
{
  char line[160];     // sets maximum linesize at three times reasonable
  char* s = &line[0]; // s and line are nearly each other's  alias
  int linesize;
  char* ptr;
  int nread;

  int fd = open("test.dat",O_RDONLY);

  linesize = 0; s = &line[0];
  while((nread = read(fd,s,1))==1) {if (*s != '\n') {s++; linesize++;} else break;}
   
/***
  here nread = EOF 0,ERROR 1 
       linesize is posibly zero, possibly greater than zero
***/

  if (linesize != 0) {ptr = malloc(linesize*sizeof(char));}
  if (linesize != 0) memcpy(ptr,line,linesize);
  *qtr = ptr;
  return linesize;
}
int main()
{
    int linesize;
    char*  ptr;
    char** qtr = &ptr;

    linesize = funy(qtr);   //sets ptr

    write(1,ptr,linesize); write(1,"\n\r",2);
}

