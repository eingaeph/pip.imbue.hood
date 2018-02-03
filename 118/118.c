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

        /*** 
           The following are returned from the keyboard as escape squences
           not as single (ascii) characters
        ***/

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

/*** function declarations ***/

void window(int xmin, int xmax, int ymin, int ymax);
void die(const char *s);
int  ReadKey(void);
int  encode(int count, char *seq);
void writeDigit(int digit, int fildes);
int  edal(int retval, int fetch);
void init(int argc, char **argv);
int  getl(char **qtr);
int  readAline(void);
void enter(void);
void buildScreenBuffer(int star, int stop);
int  getCursorPosition(int *rows, int *cols);
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

int ReadKey() 
{
  char c; int nread;

  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) 
  if (nread == -1 && errno != EAGAIN) die("terminated in readkey");
  else ; // write(STDIN_FILENO,"*",1); 
  write(STDOUT_FILENO,"\n\r",2);
 
  if (c == (char) CTRL_Q) exit(0);  // CTRL-q is 17 in decimal

  if (c != 27) return c; 

  
  char seq[3]={' ',' ',' '}; int count = 1;
  for (int n = 0; n < 3; ++n) 
   {if (read(STDIN_FILENO, &seq[n], 1) == 1) {count++;}
    else break;}

  int retval;
  if (count > 1) retval = encode(count, seq);

  return retval;
}

/*** handle escape sequences. ***/

int encode (int count, char* seq)
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

  write(STDOUT_FILENO,"seq[1] = ",9); write(STDOUT_FILENO,&seq[1]    ,1);
  write(STDOUT_FILENO,"\n\r"     ,2);

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

void enter(void)
{
}

void adal(void)    // add a line
{
      // state: ix text insertion point coordinate
      // state: iy text insertion point coordinate
      // state: ENTER
      // state: iy == iymax
      // state: lastline

      // action: malloc new line firs
      // action: malloc new line seco
      // populate new line firs
      // populate new line seco
   
      // calculate: iy_firs
      // calculate: iy_seco
      
      // malloc new with space for an extra line 
      // populate new

      // free text
      // malloc text with space for extra line
 
    slot *new  = (slot *)malloc(10*sizeof(slot));
    slot *old  = (slot *)malloc(10*sizeof(slot));

    int j;

    slot newline;
    char *ptr = "Hello world!";
    newline.row = ptr;
    newline.size = strlen(ptr);

    for (j = 0; j < 10; j++) 
      {if (j != 3) {new[j] = text[j];}
       else        {new[j] = newline;}
      }
}

int edal(int retval, int fetch)
{
  char c = retval;         // retrieve a 1 byte character 
                           // from a 4 byte integer

  int fpt = iovars.fptra;
  int insertionPoint = cord.ix; 

  if (retval == BACKSPACE  & cord.ix != 0) {cord.ix-- ; return 0;}
  if (retval == ARROW_LEFT & cord.ix != 0) {cord.ix-- ; return 0;}
  if (retval == ARROW_RIGHT)               {cord.ix++ ; return 0;}
  if (retval == ENTER)                     {enter();    return 0;}

  int test = (c > 31 && c < 127); // true for printable character
  if (!test) return 0;
 
  write(fpt, ClearScreen,strlen(ClearScreen));

  int limit = text[fetch].size + 1 ; 
  char *new = malloc((limit)*sizeof(char));
  char *chng = new;
  char *orig = text[fetch].row;

  int no; 
  for (no = 0 ; no < limit; no++)
    {
     if (no != cord.ix)  {*chng = *orig; chng++; orig++;}
     else                {*chng = c; chng++;}
    }

  free(text[fetch].row); 
  text[fetch].row = new; text[fetch].size = limit; cord.ix++;

  write(fpt,text[fetch].row,text[fetch].size); write(fpt,"\n\r",2);

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
    iovars.fptra = open("/dev/pts/18", O_RDWR);

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

    cord.cu = 1;    /*screen coordinates */
    cord.cv = 1;
            
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
  raw.c_cflag |=  (CS8);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  raw.c_cc[VMIN]  = 0;
  raw.c_cc[VTIME] = 1;

  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

void c3a(int retval) // choose amongst alternative actions
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
    int retval = ReadKey();

    cord.iy  = 4;

    edal(retval, cord.iy);

    window(0,79,0,6);
   }
  return 0;
}

