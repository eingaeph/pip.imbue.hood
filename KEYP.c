#! /usr/bin/tcc -run 

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios orig_termios;

void disableRawMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
  tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(disableRawMode);

  struct termios raw = orig_termios;
  raw.c_lflag &= ~(ECHO | ICANON);

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

char c1 = ' ';
char c2 = ' ';
char c3 = ' ';
char c4 = ' ';

int main() {
  enableRawMode();

  char c;
  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
    if (iscntrl(c)) {
      printf("%d\n", c);
    } else {
      printf("%d ('%c')\n", c, c);
    }
   c4=c3; c3=c2; c2=c1; c1=c;
   int t4 = 27; int t3 = 91; int t2 = 50; int t1 = 126;
   char s4 = t4; char s3 = t3; char s2 = t2; char s1 = t1;
  if ((c4 == s4) && (c3==s3) && (c2 == s2) && (c1 == s1)) {printf("insert\n");}
  }

  return 0;
}
