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

void writeDigit(int digit);

/*** Numeric Codes for Escape Sequences ***/

enum KEY_ACTION
{
        KEY_NULL = 0,       /* NULL */
        CTRL_C = 3,         /* Ctrl-c */
        CTRL_D = 4,         /* Ctrl-d */
        CTRL_F = 6,         /* Ctrl-f */
        CTRL_H = 8,         /* Ctrl-h */
        TAB = 9,            /* Tab */
        CTRL_L = 12,        /* Ctrl+l */
        ENTER = 13,         /* Enter */
        CTRL_Q = 17,        /* Ctrl-q */
        CTRL_S = 19,        /* Ctrl-s */
        CTRL_U = 21,        /* Ctrl-u */
        ESC = 27,           /* Escape */
        BACKSPACE =  127,   /* Backspace */

        /* The following are just soft codes, not really reported by the
         * terminal directly. */

        ARROW_LEFT = 1000,
        ARROW_RIGHT,
        ARROW_UP,
        ARROW_DOWN,
        INSERT_KEY,
        DEL_KEY,
        HOME_KEY,
        END_KEY,
        PAGE_UP,
        PAGE_DOWN
};


/*** handle escape sequences. ***/

char encode (int count, char* seq)
{
  write(1,"encode at work  ",16);
  write(1,"count = ",8);
  writeDigit(count);
  write(1,"  ",2);

  char buf[] = "   ";

  buf[0] = seq[0] ; write(STDOUT_FILENO,buf,1); 
  buf[0] = seq[1] ; write(STDOUT_FILENO,buf,1); 
  buf[0] = seq[2] ; write(STDOUT_FILENO,buf,1); 
  write(1,"\n\r",2);

  int testa = ( (seq[0] == '[')); 
  int testb = ( (count < 4 ) );
  int testc = ( (seq[2] == '~') );

  if (count < 3 ) return ESC;  // this is unusual
   
  if (!testa)     return ESC;

  if (testb) {
     switch(seq[1]) {
        case 'A': return ARROW_UP;
        case 'B': return ARROW_DOWN;
        case 'C': return ARROW_RIGHT;
        case 'D': return ARROW_LEFT;
        case 'H': return HOME_KEY;
        case 'F': return END_KEY;                            }
              }

  if (testc) {
     switch(seq[1]) {
        case '2': return INSERT_KEY;
        case '3': return DEL_KEY;
        case '5': return PAGE_UP;
        case '6': return PAGE_DOWN;
                    }
             } // else return ESC;  
     
  return ESC; // this is unusual 
}
    
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
  char buf[] = "      ";
   snprintf(buf,6,"%d",digit);
   write(STDOUT_FILENO,buf,strlen(buf));
   return;
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

  char seq[3]={' ',' ',' '}; int count = 1;
 
  if (read(STDIN_FILENO, &seq[0], 1) == 1) {count++;}
  if (read(STDIN_FILENO, &seq[1], 1) == 1) {count++;}
  if (read(STDIN_FILENO, &seq[2], 1) == 1) {count++;}

  if (count > 1) {
                  c = encode(count,seq);
                 }

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



