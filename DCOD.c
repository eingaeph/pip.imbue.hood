#! /usr/bin/tcc -run 

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

enum KEY_ACTION{
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
        DEL_KEY,
        HOME_KEY,
        END_KEY,
        PAGE_UP,

        PAGE_DOWN
};

struct parse
{
       int seqno;         // seqno > 0 implies delay processing
       int pr;            // process retchar
       int retchar;      // return character 
};          

struct parse decode = { .seqno = 0, .pr = 1 }; //decode is global 


//  a- c != 27 && seqno == 0   retval = c;
//  b- c == 27 && seqno == 0   seqno = 1 ; retval = ?;
//  d- c != 91 && seqno == 1   seqno = 0 ; retval = possible; 
//  e- c == 91 && seqno == 1   seqno = 2 ; retval = ?;
// int testa = (c==72)||(c==70)||(c==65);
//  f- testa   && seqno == 2   seqno = 0 ; retval = arrows;
// int testb = (c==50)||(c==51)||)c==53)||(c==54);
//  g- testb   && seqno == 2   seqno = 3 ; retval = ?;

int uncode(char c) {

  static char seq[4];

  if ((c != 27) && (decode.seqno == 0 )) 
     {//printf ("nop %d \n",c);
      decode.pr=1; 
      decode.retchar = (int) c ; return 0;}

  if ((c == 27) && (decode.seqno == 0))
     {decode.seqno = 1;
      printf("unheralded esc character; start delayed processing %d\n",c);
      decode.pr = 0;
      return 1; }

  int testa = (c==72)||(c==70);                   // home, end
  int testb = (c==65)||(c==66)||(c==67)||(c==68); // arrow up, down, right, left
  int testc = (c==50)||(c==51)||(c==53)||(c==54); // page up, page down, insert, delete

  int testd = (testa || testb||testc);

  int teste = !testd;

  if (( c != 91 ) && (decode.seqno == 1)) 
     {//printf("not a esc seq; processing enabled\n",c);
      decode.seqno = 0;
      decode.retchar = (int) c;
      decode.pr = 1; 
      return 2;}

  if (( c == 91 ) && (decode.seqno == 1))
     {//printf("second escape: delay processing %d\n",c);
      decode.seqno=2;
      decode.pr=0; 
      return 3;}

  if ((testa || testb) && (decode.seqno == 2)) 
     {printf("ending short escape sequence %d\n",c);
      decode.seqno = 0;
      decode.pr=1;
      decode.retchar= 1000;
      return 4;}

  if (testc && (decode.seqno == 2))
     {//printf("still processing escape seq %d\n",c);
      decode.seqno = 3;
      decode.pr=0;
      return 5;}

  if ((c == 126) && (decode.seqno == 3))
     {printf("ending long escape sequence %d\n",c);
      decode.seqno = 0;
      decode.retchar = 1000;
      decode.pr=1;
      return 6;}

  printf("reaching here is unusual c = %d\n",c);
  decode.pr=1;
  decode.retchar = (int) c;
  decode.seqno = 0; return 7;
}

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

int main() 
{
  enableRawMode();

  int nread;
  char c, seq[3];

  while (1) 
{   
    nread = read(STDIN_FILENO,&c,1);  //character string from keypresses

    if ( c == 'q' ) return 0;

    int ignore = uncode(c);

    if (!decode.pr) {continue;} // working on escape sequence

    if (decode.retchar < 1000) 
    
    {c = (char) decode.retchar;
      if (iscntrl(c)) {printf("%d\n", c);} 
      else {printf("%d ('%c')\n", c, c);}
    }
    
    else {printf("000 arrows, etcetera %d\n", decode.retchar); 
          continue;}
}

  return 0;
}
