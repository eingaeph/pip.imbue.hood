#! /usr/bin/tcc -run

#include <unistd.h>   //read,write
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h> //open,close per Kerrisk page 72
#include <fcntl.h>    //open,close per Kerrisk page 72

#include <ctype.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <termios.h>

/***
    REAF, ADAL, NCOD
***/

/***
    global variables
***/

    size_t linecap;
    int nread;
    struct { int fp; int nread; } nput;

typedef struct slot
{
    ssize_t size;
    char *row;
    int count;
}   slot;

    slot line;
    slot *text;

struct termios orig_termios;

/***
   function declarations
***/

int encode (int count, char* seq);

void die(const char *s);

void disableRawMode();

void enableRawMode();

void writeDigit(int digit);

char ReadKey();

int getr(char **qtr);

int addAline(int here,int maxndx);

int deleteAline(int omit,int maxndx);

void etxt(int maxndx);

int replaceAline(int nsrt,int maxndx);

int readAline(void);

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
        DEL_KEY,
        HOME_KEY,
        END_KEY,
        PAGE_UP,
        PAGE_DOWN
};

/*** handle escape sequences. ***/

int encode (int count, char* seq)
{
  write(1,"encode at work  ",16);
  write(1,"count = ",8);
  writeDigit(count);
  write(1,"  ",2);

  char buf[] = "   ";
//  writeDigit(seq[0]);
  buf[0] = seq[0] ; write(STDOUT_FILENO,buf,1); 
  buf[0] = seq[1] ; write(STDOUT_FILENO,buf,1); 
  buf[0] = seq[2] ; write(STDOUT_FILENO,buf,1); 
  write(1,"\n\r",2);


  int testa = ( (seq[0] == '['));   
  int testb = ( ( testa ) && (seq[1] >= '0') && (seq[1] <='9') );
  int testc = ( ( testb ) && (count < 4 ));
  int testd = ( ( testb ) && (seq[2] == '~') );
   

  if (testa) write(1,"testa = TRUE\n\r",14);
  if (testb) write(1,"testb = TRUE\n\r",14);
  if (testc) write(1,"testc = TRUE\n\r",14);
  if (testd) write(1,"testd = TRUE\n\r",14);
  
  if (count < 3 ) return ESC;
  
  return ESC;
}
/*
  if (seq[0] == '[') 
     {
      if (seq[1] >= '0' && seq[1] <= '9') 
            {
             // Extended escape, read additional byte. 
             if (count  == 3) return ESC;
             if (seq[2] == '~') 
                {
                 switch(seq[1]) {
                 case '3': return DEL_KEY;
                 case '5': return PAGE_UP;
                 case '6': return PAGE_DOWN;
                                }
                 }
             else {
             switch(seq[1]) {
                 case 'A': return ARROW_UP;
                 case 'B': return ARROW_DOWN;
                 case 'C': return ARROW_RIGHT;
                 case 'D': return ARROW_LEFT;
                 case 'H': return HOME_KEY;
                 case 'F': return END_KEY;
                             }
                  }
            }
}

            // ESC O sequences. 
            else if (seq[0] == 'O') {
                switch(seq[1]) {
                case 'H': return HOME_KEY;
                case 'F': return END_KEY;
                }
            }
            break;
        default:
            return c;
        }
    }
}

*/

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

  char test = 27;
  if (c != test) return c; 

//  write(STDOUT_FILENO,"escape = ",9);
//  writeDigit(c);
//  write (STDOUT_FILENO,"\r\n",2);

  char seq[3]={' ',' ',' '}; int count = 1;
 
  if (read(STDIN_FILENO, &seq[0], 1) == 1) {count++;}
  if (read(STDIN_FILENO, &seq[1], 1) == 1) {count++;}
  if (read(STDIN_FILENO, &seq[2], 1) == 1) {count++;}

//  write (STDOUT_FILENO,"count = ",9);
//  writeDigit(count);
//  write (STDOUT_FILENO,"\r\n",2);

  if (count > 1) {int ignore = encode(count,seq);}

  return c;
}


int getr(char **qtr) // getline replacement
{
  char line[240];     // sets maximum linesize at three times reasonable
  char* s = &line[0]; // s and line are nearly each other's  alias
  int linesize;
  char* ptr;

  linesize = 0; s = &line[0];
  while((nread = read(nput.fp,s,1))==1) {if (*s != '\n') {s++; linesize++;} else break;}
   
/***
  here nread = EOF 0,ERROR 1 
       linesize is posibly zero, possibly greater than zero
***/

  if (linesize != 0) {ptr = malloc(linesize*sizeof(char));}
  if (linesize != 0) memcpy(ptr,line,linesize);
  if (linesize != 0) *qtr = ptr;
  return linesize;
}

int addAline(int here,int maxndx)

{
    int newlen = maxndx + 1 + 1;
    slot *new  = (slot *)malloc(newlen*sizeof(slot));

    slot newline;
    char *ptr = "Yes, I am a new line!\n";
    newline.size = strlen(ptr)-1;
    char *qtr = (char *)malloc(strlen(ptr)-1);
    memcpy(qtr,ptr,strlen(ptr)); 
    newline.row = qtr;

    slot *old = text; 

    int i,j,k; i = 0; j = 0; k = 0;
    for (i = 0 ; i < maxndx + 1 ; i++) 
      {if (i != here) {new[j] = old[k]; j++; k++;}
       else           {new[j] = old[k]; j++; k++;
                       new[j] = newline;     j++;}
      }


    free(text); text = new;  
   
    maxndx++;
    return maxndx;
}

int deleteAline(int omit,int maxndx)
{
    int newlen = maxndx + 1 - 1;
    slot *new  = (slot *)malloc(newlen*sizeof(slot));

    slot *old = text; 

    int i,j,k; i = 0; j = 0; k = 0;
    for (i = 0 ; i < maxndx + 1 ; i++) 
      {if (i != omit) {new[j] = old[k]; j++; k++;}
       else           {                      k++;}
      }

    free(text[omit].row);
    free(text); text = new;  

    maxndx--;
    return maxndx;
}

void etxt(int maxndx)
{
    write(1,"\n",1);

    int i;
    for (i = 0; i < maxndx + 1; i++)
      {
       write(1,"text[",5);
       char buf[7];
       snprintf(buf,3,"%2d",i);
       write(1,buf,2);
       write(1,"].row: ",7);
       write(1,text[i].row,text[i].size); 
       write(1,"\n\r",2);
      } 
    return;
}

// function replaceAline 
// makes one call to malloc for replacement text  
// plus  one call to free text[nsrt].row (the replaced element)
// plus  one call to free text (the entire replaced document)

int replaceAline(int nsrt,int maxndx)
{
    int newlen = maxndx + 1 + 0;
    slot *new  = (slot *)malloc(newlen*sizeof(slot));

    slot newline;
    char *ptr = "Hello World! I am a replacement line.\n";
    newline.size = strlen(ptr)-1;
    char *qtr = (char *)malloc(strlen(ptr)-1);
    memcpy(qtr,ptr,strlen(ptr)); 
    newline.row = qtr;

    slot *old = text; 

    int i,j,k; i = 0; j = 0; k = 0;
    for (i = 0 ; i < maxndx + 1 ; i++) 
      {if (i != nsrt) {new[j] = old[k]; j++; k++;}
       else           {new[j] = newline;j++; k++;}
      }

    free(text[nsrt].row);
    free(text); text = new;  

    return maxndx;
}

int readAline(void)
{
    line.row = 0; linecap = 0;
//  line.size = getline (&line.row, &linecap,nput.fp); 
    line.size = getr(&line.row);    

    if (line.size == -1) {return line.size;}

    if((line.count == 0)) 
         { text = (slot *) malloc(     (1+line.count)*sizeof(slot));}
    else { text = (slot *)realloc(text,(1+line.count)*sizeof(slot));}

    char * ptr = malloc(line.size*sizeof(char));
    text[line.count].row = ptr  ;
    text[line.count].size = line.size;
    memcpy(ptr,line.row,line.size);  

    line.count++; 
    return 0;
}

int main(int argc, char** argv)
{
    char* filename = argv[1];
    int numb; int retval; int lastline;

    if(argc == 1) return 0;

    write(1,argv[1],strlen(argv[1]));
    write(1,"\r\n",2);

    nput.fp = open(filename,O_RDONLY);

    line.count = 0;
    for (numb = 0 ; numb < 100; numb++) 
    {
    retval=readAline(); 
    if (nread == 0) {break;}
    lastline = line.count; 
    }
    
    close(nput.fp);
    char buf[8];
    snprintf(buf,8,"%d\n",lastline);
    write(1,buf,strlen(buf));
    write(1," lines were read\n\r",17);

    int maxndx = lastline - 1; etxt(maxndx);

    maxndx = replaceAline(5,maxndx); etxt(maxndx);

    maxndx = deleteAline(7,maxndx); etxt(maxndx);

    maxndx = addAline(2,maxndx); etxt(maxndx);

/***

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

***/


    return 0;
 }

