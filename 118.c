#! /usr/bin/tcc -run

/***
   init readAline
   keypress wait intercept
   keypress code translater
   getCursorPosition
   buildScreenBuffer

***/

/*** includes ***/

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h> //open,close per Kerrisk page 72
#include <fcntl.h>    //open,close 

/*** global symbols ***/

struct termios orig_termios;

struct {int fpinp; int nread; int fptra; } iovars;

typedef struct {ssize_t size; char *row; int count;} slot;

    slot line;  // set in readAline
    slot buff;  // set in edal
    slot *text;
    slot *display;

struct 
{

    int x,y;                   /* char no, line no, text coordinates */
    int ix,iy;                 /* insertion point, text coordinates */

    int xmin,xmax,ymin,ymax;   /* window edges in text coordinates  */ 

    int u,v;                   /* char no, line no */
    int cu,cv;                 /* cursor position in screen coordinates */

    int umin,umax,vmin,vmax;   /* window edges in screen coordinates */

} cord;

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
        PAGE_DOWN,
        INSERT_KEY
};

/*** function declarations ***/

void window(int xmin, int xmax, int ymin, int ymax);
void die(const char *s);
char ReadKey(void);
char encode(int count, char *seq);
void writeDigit(int digit, int fildes);
int edal(char c, int fetch);
void init(int argc, char **argv);
int getl(char **qtr);
int readAline(void);
void buildScreenBuffer(int star, int stop);
int getCursorPosition(int *rows, int *cols);
void disableRawMode(void);
void enableRawMode(void);
int main(int argc, char **argv);

/*** function definitions ***/

void window(int xmin, int xmax, int ymin, int ymax)
{
    int y;
    for (y = ymin; y < ymax + 1; y++) 
  {
    char *s = xmin + text[y].row; 

    int no;
    for ( no = 0; no + xmin < xmax + 1; no++)     
    {
    if (no+1>text[y].size) {break;}; 
    if (*s == '\n')        {break;};
    write(STDOUT_FILENO,s,1); s++;
    }
    write(STDOUT_FILENO,"\n\r",2);
  }
}

void die(const char *s) {
  write(STDOUT_FILENO, "\x1b[2J", 4);
  write(STDOUT_FILENO, "\x1b[H", 3);

  perror(s);
  exit(1);
}

char ReadKey() 
{
  char c; int nread;

  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) 
  if (nread == -1 && errno != EAGAIN) die("terminated in readkey");
  else  write(STDIN_FILENO,"*",1); 
  write(STDOUT_FILENO,"\n\r",2);
 
  if (c == 17) exit(0);  // CTRL-q is 17 in decimal

  if (c != 27) return c; 

  
  char seq[3]={' ',' ',' '}; int count = 1;
  for (int n = 0; n < 3; ++n) 
   {if (read(STDIN_FILENO, &seq[n], 1) == 1) {count++;}
    else break;}

  
  if (count > 1) c = encode(count, seq);

  return c;
}

/*** handle escape sequences. ***/

char encode (int count, char* seq)
{
  write(1,"encode at work  ",16);
  write(1,"count = ",8);
  writeDigit(count,STDOUT_FILENO);
  write(1,"  ",2);

  char buf[] = "   ";

  buf[0] = seq[0] ; // write(STDOUT_FILENO,buf,1); 
  buf[0] = seq[1] ; // write(STDOUT_FILENO,buf,1); 
  buf[0] = seq[2] ; // write(STDOUT_FILENO,buf,1); 
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

void writeDigit(int digit,int fildes)
{
  char buf[20];
   snprintf(buf,4,"%d\0",digit);
   write(fildes,buf,strlen(buf));
}

int edal(char c, int fetch)
{
  int fpt = iovars.fptra;
  int insertionPoint = cord.ix; 

  char ClearScreen[]= "\x1b[2J"; 
  write(fpt, ClearScreen,4);
  write(fpt,"\r\nat entry \r\n",13);
  write(fpt,buff.row,buff.size); 
  write(fpt,"\r\n",2);

  write(fpt,"fetch = ",9);
  writeDigit(fetch, fpt);
  write(fpt,"\r\n",2);

  int test = (c > 31 && c < 127); // true for printable character
  if (c == ARROW_RIGHT) {cord.ix++ ; return 0;}
  if (!test) return 0;

  int limit = text[fetch].size + 1 ; 
  char *new = malloc((limit)*sizeof(char));
  char *chng = new;
  char *orig = text[fetch].row;

  // "insert %c at position %d\n"

  int no; 
  for (no = 0 ; no < limit; no++)
    {
     if (no != cord.ix)  {*chng = *orig; chng++; orig++;}
     else                {*chng = c; chng++;}
    }

  free(text[fetch].row); 
  text[fetch].row = new;
  text[fetch].size = limit;
  cord.ix++;

  write(fpt,text[fetch].row,text[fetch].size); write(fpt,"\n\r",2);

  char mesy[] = "eal is finished\n"; write(fpt,mesy,strlen(mesy));
  int ignore; read(STDIN_FILENO, &ignore, 1); // pause, wait for input 

  return 0;

}

void init(int argc, char** argv)
{
    int numb; int retval; int lastline;
    char *outt;

    if (argc == 1) return;

    enableRawMode();

    char * filename = argv[1];
    write(STDOUT_FILENO,filename,strlen(filename)); 
    write(STDOUT_FILENO,"\n\r",2);

    display = malloc(     (60)*sizeof(slot));

    iovars.fpinp = open(filename,O_RDONLY);
    iovars.fptra = open("/dev/pts/4", O_RDWR);

    line.count = 0;
   for (numb = 0 ; numb < 100; numb++) 
    {
     retval=readAline(); 
     if (iovars.nread == 0) {break;}
     lastline = line.count; 
    }

    char mesa[]="lastline = ";

    write(STDOUT_FILENO,mesa,strlen(mesa));
    writeDigit(lastline,STDOUT_FILENO);
    write(STDOUT_FILENO,"\n\r",2);

    cord.ix = 0; 
    cord.iy = 0;    /* insertion point, text coordinates */

    cord.xmin =  0;
    cord.xmax = 79;
    cord.ymin =  0;
    cord.ymax = 23;   

    cord.cu = 0;    /*screen coordinates */
    cord.cv = 0;
            
    cord.umin = 1;
    cord.umax = 80;
    cord.vmin = 1;
    cord.vmax = 24;

    buff.row  = malloc(1*sizeof(char));
    buff.size = 1;

  
}

int getl(char **qtr)    // getline work-alike
{
  char test[1];
  char inLine[240];     // sets maximum linesize at three times reasonable
  char* ptr;

  int nread; 
  int inLineSize = 0; 
  char *s = &inLine[0];   //s and inLine are aliases of each other
  while((iovars.nread = read(iovars.fpinp,s,1))==1) 
    {if (*s != '\n') {s++; inLineSize++;} else break;}

  if (inLineSize  > 0) {ptr = malloc(inLineSize*sizeof(char));
                        memcpy(ptr,inLine,inLineSize);
                       *qtr = ptr;}

  return inLineSize;
}

int readAline(void)
{
    line.row = 0; 
    line.size = getl(&line.row);    

    if (line.size == 0) {return line.size;}

    if((line.count == 0)) 
         { text = (slot *) malloc(     (1+line.count)*sizeof(slot));}
    else { text = (slot *)realloc(text,(1+line.count)*sizeof(slot));}

    char * ptr = malloc(line.size*sizeof(char));
    text[line.count].row = ptr  ;
    text[line.count].size = line.size;
    memcpy(ptr,line.row,line.size);  

    line.count++; 
    return line.size;
}

void buildScreenBuffer(int star, int stop)
{
}


int getCursorPosition(int *rows, int *cols) 
{
}

/* Raw mode: 1960's magic numbers (grumble). */

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

void c3a(c) // choose amongst alternative actions
{


/*** add character before ip                ***/
/*** delete character under ip              ***/
/*** overwrite character under ip           ***/

/*** insert: toggle insert overwrite        ***/
/*** home: set ip to home position          ***/
/*** end: set ip to end position            ***/
/*** enter: split line                      ***/
/*** ctrl-k: delete line                    ***/
/*** back space: decrement ip               ***/

}
int main(int argc, char** argv)
{

  init(argc, argv);

  while (1) 
   {
    char c = ReadKey();

    edal(c,3);

    window(0,79,0,6);

   }
  return 0;
}

