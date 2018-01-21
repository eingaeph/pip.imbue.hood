#! /usr/bin/tcc -run

/*** includes ***/

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

struct termios orig_termios;


void writeDigit(int digit)
{
  char buf[] = "      ";
   int leng = snprintf(buf,6,"%d",digit);
   write(STDOUT_FILENO,buf,leng);
   return;
}

/*** terminal ***/

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

char ReadKey() 
{
  char c; int nread;
  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) 
  if (nread == -1 && errno != EAGAIN) die("read");

  if (c == 17) write(STDOUT_FILENO,"\r\n",2); // CTRL-q 
  if (c == 17) exit(0);

  char test = 27;
  if (c != test) return c; 


  return c;
}

int main() {

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

  return 0;
}



