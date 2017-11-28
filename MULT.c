#! /usr/bin/tcc -run

/* MULT.c Parse MULT iple character keystroke codes */

/*** includes ***/

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

/*** VT100 Display Control Escape Sequences ***/

char ClearScreen[]=                          "\x1b[2J";
char CursorToTopLeft[] =                     "\x1b[H";
char TildeReturnNewline[] =                  "~\r\n";

char ReturnNewline[] =                       "\r\n";

/*
two sequences
C is cursor foward, but don't exit the screen
B is cursor down, but don't exit the screen
999 is a large enough maximum number of steps
*/

char CursorToMaxForwardMaxDown[]=           "\x1b[999C\x1b[999B";
char GetCursorPosition[] =                  "\x1b[6n";

/*
the terminal reply to GetCursorPosition   "24;80R" or similar
*/

char CursorHide[]=                          "\x1b[?25l";
char CursorDisplay[]=                       "\x1b[?25h";
char ClearCurrentLine[]=                    "\x1b[K";
char CursorToCenter[]=                      "\x1b[12;30f";

//Force Cursor Position	<ESC>[{ROW};{COLUMN}f
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

/*** write (to the screen) ***/

void writeDigit(int digit)
{
//char buf[] = "abcdefghijklmnopqrstuvwxyz";
  char buf[] = "                          ";
   snprintf(buf,4,"%d",digit);
   write(STDOUT_FILENO,buf,4);
   return;
}
char ReadKey() 
{
  char c; int nread;
  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) 
  if (nread == -1 && errno != EAGAIN) die("read");

  if (c == 17) write(STDOUT_FILENO,"\r\n",2);
  if (c == 17) exit(0);

//char buf[] = "abcdefghijklmnopqrstuvwxyz";
  char buf[] = "                          ";
  snprintf(buf,15,"\r\nnread = %d",nread); 
  write(STDOUT_FILENO,buf,15);

  char test = 27;
  if (c != test) return c; 

  snprintf(buf,20,"\r\nescape = %d",c); 
  write(STDOUT_FILENO,buf,20);


  char seq[3]; int count = 1;
 
  if (read(STDIN_FILENO, &seq[0], 1) == 1) {count++;}
  if (read(STDIN_FILENO, &seq[1], 1) == 1) {count++;}
  if (read(STDIN_FILENO, &seq[2], 1) == 1) {count++;}

  char ReturnNewline[] =                       "\r\n";
  write(STDOUT_FILENO,"\r\ncount = ",10);
  writeDigit(count);
  return c;
}

int main() {

  enableRawMode();

  while (1) 
{
    char c = ReadKey();
    write (STDOUT_FILENO, "\r\nc = ", 6);
    writeDigit(c); 
//    if (iscntrl(c)) {printf("%d\n", c);} 
//    else            {printf("%d ('%c')\n", c, c);}
}

  return 0;
}



