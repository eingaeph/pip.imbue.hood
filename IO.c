#! /usr/bin/tcc -run

/*** 
   IO prototype  
   Read a file line by line 
***/

/*** includes ***/

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

/***  formatted printing ***/

void writeDigit(int digit)
{
  char buf[] = "      ";
   snprintf(buf,6,"%d",digit);
   write(STDOUT_FILENO,buf,strlen(buf));
   return;
}

/*** terminal ***/

struct termios orig_termios;

void die(const char *s) {
  write(STDOUT_FILENO, "\x1b[2J", 4);
  write(STDOUT_FILENO, "\x1b[H", 3);

  perror(s);
  exit(1);
}

void disableRawMode() {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
    die("tcsetattr");
}

void enableRawMode() {
  if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr");
  atexit(disableRawMode);

  struct termios raw = orig_termios;
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;

  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

/*** write (to the screen) ***/


int main() {

 enableRawMode();
 char line[100];    //
 char* s = &line[0];
 int fd = open("test.dat",O_RDONLY);

 int count; int numb = 0;
// for (count = 0; count < 40; count++)
while(read(fd,s,1)==1)
{
// int ignore = read(fd,s,1);

 if (*s == '\n') {
                  writeDigit(numb);numb = 0;
                  continue;
                 }
 write(1,s,sizeof(*s));
 s++; numb++;
}
 write(1,"\n\r",2);
 close(fd);
 exit(0);
}



