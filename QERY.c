#! /usr/bin/tcc -run 

/* a simple keypress decoder */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

struct termios orig_termios;

typedef struct slot
{
    ssize_t size;
    char *row;
    int count;
}   slot;

    slot line;
    slot *text;

struct 
{

    int x,y;                   /* char no, line no, text coordinates */
    int ix,iy;                 /* insertion point, text coordinates */

    int xmin,xmax,ymin,ymax;   /* window edges in text coordinates  */ 

    int u,v;                   /* char no, line no */
    int cu,cv;                 /* cursor position in screen coordinates */

    int umin,umax,vmin,vmax;   /* window endges in screen coordinates */

} cord;

void screenBuffer(int star, int stop)
{
    printf("%s","screenBuffer at work\n");
    slot* display = (slot *) malloc(     (25)*sizeof(slot));
    for (int i=0; i<25; i++) {display[i].size  =   3;
                              display[i].row   = "~\r\n";
                              display[i].count =   0;}

    int dy = 0;
    display[dy].row  = "kilo.c welcomes you\n";
    display[dy].count = 0;
    display[dy].size = strlen(display[dy].row);

    dy++;
    display[dy].row  = "kilo.c\n";
    display[dy].count = 0;
    display[dy].size = strlen(display[dy].row);   

    int i;  
    for (int i = star; i<(stop+1); i++)
         {dy++ ; display[dy] = text[i];}

    dy = -1 ;
    for (int i = 0; i< 23; i++)
         {
          dy++ ;
          int stringLength = display[dy].size;
          char* pointerToString = display[dy].row;
          printf("%.*s", stringLength, pointerToString);
         }

}


int getCursorPosition(int *rows, int *cols) {
  char buf[32];
  unsigned int i = 0;

  if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4) return -1;

  while (i < sizeof(buf) - 1) {
    if (read(STDIN_FILENO, &buf[i], 1) != 1) break;
    if (buf[i] == 'R') break;
    i++;
  }
  buf[i] = '\0';

  if (buf[0] != '\x1b' || buf[1] != '[') return -1;
  if (sscanf(&buf[2], "%d;%d", rows, cols) != 2) return -1;

  return 0;
}

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

    buf[i] = '\0';

    
    if (buf[0] != 27 || buf[1] != '[') return -1;
                              
    int x; int y;
    if (sscanf(buf+2,"%d;%d",&x,&y) != 2) return -1;

    printf("x = %d , y = %d \n", x,y);

char CursorToMaxForwardMaxDown[]=           "\x1b[999C\x1b[999B";
char GetCursorPosition[] =                  "\x1b[6n";
     size_t size = strlen(CursorToMaxForwardMaxDown);
     write(STDOUT_FILENO,&CursorToMaxForwardMaxDown, size);

  }

  return 0;
}

