#! /usr/bin/tcc -run 

/* a simple keypress decoder */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

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

int test(char c) {
   c4=c3;        c3=c2;        c2=c1;        c1=c;
   int t4 = 27;  int t3 = 91;  int t2 = 50;  int t1 = 126;
   char s4 = t4; char s3 = t3; char s2 = t2; char s1 = t1;

   int test = (c4==s4) && (c3==s3) && (c2==s2) && (c1==s1);
   return test;
}

int main() {
  enableRawMode();

  char c;
  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
    if (iscntrl(c)) {
      printf("%d\n", c);
    } else {
      printf("%d ('%c')\n", c, c);
    }

  if (test(c)) {printf("insert\n");}

  char buf[32];
  unsigned int i = 0;

 /* Query screen for cursor location */

    if (write(1, "\x1b[6n", 4) != 4) return 0;

    while (i < sizeof(buf)-1) 
    {
        if (read(0,buf+i,1) != 1) break;
        if (buf[i] == 'R') break;
        i++;
    }

    printf("i = %d\n",i);
    buf[i] = '\0';

    int x; int y;
    if (buf[0] != 27 || buf[1] != '[') return -1;

    int leng = strlen(buf);
    printf("string length = %d\n",leng);

    printf("<esc>[24;80\n");
    int j ;
    for ( j = 2; j < 7; j++) 
    printf("j = %d buf[%d] = %d\n", j,  j, buf + j);
                              
//    sscanf(buf+2,"%d;%d",x,y);

//    if (sscanf(buf+2,"%d;%d",x,y) != 2) return -1;

//    printf("x = %d , y = %d \n", x,y);

  }

  return 0;
}

