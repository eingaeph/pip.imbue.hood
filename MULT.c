#! /usr/bin/tcc -run

/* MULT.c Pare MULTiple character keystroke codes */

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

int ReadKey() 
{
  int nread;
  char c; 
  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) 
 {if (nread == -1 && errno != EAGAIN) die("read");}
  
  char seq[3]; int count = 1;
 
  if (read(STDIN_FILENO, &seq[0], 1) == 1) {count++;}
  if (read(STDIN_FILENO, &seq[1], 1) == 1) {count++;}
  if (read(STDIN_FILENO, &seq[2], 1) == 1) {count++;}

 
  if (c == 'q') exit(0);
  if (count > 1) printf("count = %d\n",count);
  return;
}

int main() {

  enableRawMode();

  while (1) {
    ReadKey();
  }

  return 0;
}



