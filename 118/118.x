#! /usr/bin/tcc -run

/***

   keypress wait intercept translate

***/

/*** includes ***/

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h> //open,close per Kerrisk page 72
#include <fcntl.h>    //open,close 

/*** macro defines ***/

#define possibleIxIy ix = global.ix;          \
                     iy = global.iy;          \
                     assert(ix >= 0) ;        \
                     assert(iy >= 0);         \
                     assert(iy <= lastline);
 
#define writeToScreen(x)  write(STDOUT_FILENO,x,strlen(x))

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

    int lastline;              /* size of text */

} global;

 
/*** Numeric Codes for Escape Sequences, CTRL+ Keys, Others ***/

enum KEY_ACTION
{
        KEY_NULL = 0,       /* NULL   */
        CTRL_C = 3,         /* Ctrl-c */
        CTRL_D = 4,         /* Ctrl-d */
        CTRL_F = 6,         /* Ctrl-f */
        CTRL_H = 8,         /* Ctrl-h */
        TAB    = 9,         /* Tab    */
        CTRL_K = 11,        /* Ctrl+k */
        CTRL_L = 12,        /* Ctrl+l */
        ENTER  = 13,        /* Enter  */
        CTRL_Q = 17,        /* Ctrl-q */
        CTRL_S = 19,        /* Ctrl-s */
        CTRL_U = 21,        /* Ctrl-u */
        ESC    = 27,        /* Escape */
        BACKSPACE =  127,   /* Backspace */

        /*** 
The following are returned from the keyboard as escape squences 
not as single (ascii encoded) characters
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
char CursorDown[] =                          "\x1b[1B"; 
char CursorForward[] =                       "\x1b[1C";

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

int  inAline(int ix, int iy);
int  inWindow(int ix, int iy);
void delAline(void);
void setWindow(void);
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
int  main(int argc, char **argv);

/*** function definitions ***/



int arrow_down(void)
{

  int iy = global.iy; 
  int ix = global.ix;
  int ymax = global.ymax;
  int lastline = global.lastline;

  iy++; if(iy > lastline) iy = lastline;

  int size = text[iy].size;
  if (size < ix + 1 )  ix = size - 1;

//store the insertion point 

  global.ix   = ix;
  global.iy   = iy;

  return 0;

}

void buildScreenBuffer(int star, int stop)
{
}



// chin  character insert, printable

void chin(char c, int fetch)
{

  int limit = text[fetch].size + 1 ; 
  char *new = malloc((limit)*sizeof(char));
  char *chng = new;
  char *orig = text[fetch].row;

  int no; 
  for (no = 0 ; no < limit; no++)
    {
     if (no != global.ix)  {*chng = *orig; chng++; orig++;}
     else                  {*chng = c; chng++;}
    }

  free(text[fetch].row); 
  text[fetch].row = new; text[fetch].size = limit; global.ix++;

  return;

}

void delAline(void)
{
  int ix = global.ix;       //x text insertion point
  int iy = global.iy;       //y text insertion point
  int ymax = global.ymax;   // maximum y value under window 
  int lastline = global.lastline; // number of rows in text

  if (iy == (lastline - 1)) return; // delete attempt fails
 
// <new> aray of slots new with space for one less line

  slot *new  = malloc((lastline-1)*sizeof(slot));
                       
  int j; int k = 0;
  for (j = 0; j < lastline; j++)  //build array of slots new
    {
     if (j != iy) { new[k] = text[j];  k++; }
     else         { k = k ; }
    }

  global.lastline-- ; lastline = global.lastline; 
  free(text[iy].row);
  global.ix = 0;
  if (lastline < (ymax + 1)) global.ymax = lastline - 1;

  text = realloc(text,lastline*sizeof(slot));
  for (j = 0; j < lastline; j++) text[j] = new[j];

  free(new);
  return; 
 
}

// chin  character insert, printiable

void del_key(int fetch)
{

  int limit = text[fetch].size - 1 ; 
  char *new = malloc((limit)*sizeof(char));
  char *chng = new;
  char *orig = text[fetch].row;

  int no; 
  for (no = 0 ; no < limit; no++)
    {
     if (no != global.ix)  {*chng = *orig; chng++; orig++;}
     else                  { orig++ ;} // skipping
    }

  free(text[fetch].row); 
  text[fetch].row = new; text[fetch].size = limit; 

  int testa = inAline(global.ix,global.iy);
  int testb = inWindow(global.ix,global.iy);

  if (!(testa && testb)) die("quitting in del_key");

  return;

}

void die(const char *s) {
  writeToScreen(CursorDisplay);
//  writeToScreen(ClearScreen);
//  writeToScreen(CursorToTopLeft); 
//  perror(s);
  writeToScreen(s); writeToScreen("\n\r");
  exit(1);
}

void disableRawMode() 
{
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
    die("tcsetattr");
}
int edal(int retval, int fetch)
{
  char c = retval;         // retrieve a 1 byte character 
                           // from a 4 byte integer


  int ix   = global.ix;     // previous values of ix,iy
  int iy   = global.iy;
  int ymax = global.ymax;   // previous values of xmax,etc. 


  int test = (retval > 31 && retval < 127); // true for printable character

  if (test)                             {chin(c,fetch); return 0;}     
  if (retval == BACKSPACE  & ix != 0)   {global.ix-- ;  return 0;}
  if (retval == ARROW_LEFT & ix != 0)   {global.ix-- ;  return 0;}
  if (retval == ARROW_RIGHT)            {global.ix++ ;  return 0;}
  if (retval == ARROW_UP   & iy != 0)   {global.iy-- ;  return 0;}
  if (retval == ARROW_DOWN )            {arrow_down();  return 0;}
  if (retval == ENTER)                  {enter();       return 0;}
  if (retval == CTRL_K)                 {delAline();    return 0;}
  if (retval == DEL_KEY)                {del_key(fetch);return 0;} 
  if (retval == HOME_KEY)               {global.ix = 0; return 0;} 

  return 0;

}



/* Raw mode: 1960's magic numbers (grumble). */


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


/*** handle escape sequences. ***/

int encode (int count, char* seq)
{
//  write(1,"encode at work  ",16);
//  write(1,"count = ",8);
//  writeDigit(count,STDOUT_FILENO);
//  write(1,"  ",2);

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

//  write(STDOUT_FILENO,"seq[1] = ",9); write(STDOUT_FILENO,&seq[1]    ,1);
//  write(STDOUT_FILENO,"\n\r"     ,2);

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


void enter(void)
{
  int ix = global.ix;    //text x insertion point
  int iy = global.iy;    //text y insertion point
  int lastline = global.lastline; // number of rows in text
  int lena = ix; // length of newline firs
  int lenb = text[iy].size - lena; //length of newline seco


/*** build firs and seco ***/

  char *firs = malloc(lena*sizeof(char)); //string firs
  char *seco = malloc(lenb*sizeof(char)); //string seco

  char *chng = firs; // populate firs length lena 
  char *orig = text[iy].row; 
  int no; for (no = 0 ; no < lena; no++)
    {*chng = *orig; chng++; orig++;}

  chng = seco;       // populate seco length lenb
  for (no = lena ; no < lena + lenb; no++)
    {*chng = *orig; chng++; orig++;}

//build aray of slots new with space for extra line

  slot *new  = malloc((lastline+2)*sizeof(slot));
                      
  int j; int k = 0;

  for (j = 0; j <= lastline; j++)  //build an array of slots
    {
     if (j != iy) { new[k] = text[j];   k++; }
     else         { 
                    new[k].row = firs; new[k].size = lena; k++;
                    new[k].row = seco; new[k].size = lenb; k++; 
                  }
    }


  free(text[iy].row);

  global.lastline ++; lastline = global.lastline; 
  global.ix = 0; global.iy++;

  text = realloc(text,lastline*sizeof(slot));
  for (j = 0; j <= lastline; j++) text[j] = new[j];

  free(new);


}
int getCursorPosition(int *rows, int *cols) 
{
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



int inAline(int ix, int iy)    /* test ix iy ok, in a line    */
{
  
    int lastline = global.lastline;  
    int size = text[iy].size;

    int testa = (iy <= lastline) && (iy >= 0); 
    int testb = (ix <= size )    && (ix >= 0);
  
    return testa && testb;     /* returns true in a line      */

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

   for (numb = 0 ; numb < 100; numb++) 
    {
     retval=readAline(); 
     if (iovars.nread == 0) {break;}
     lastline = numb; 
    }

    char mesa[]="lastline = ";

    write(STDOUT_FILENO,mesa,strlen(mesa));
    writeDigit(lastline,STDOUT_FILENO);
    write(STDOUT_FILENO,"\n\r",2);

    global.ix = 0; 
    global.iy = 0;    /* insertion point, text coordinates */

    global.xmin =  0;
    global.xmax = 79;
    global.ymin =  0;
    if (lastline < 24) global.ymax = lastline;
    else               global.ymax = 23; 

    global.cu = 0;    /*screen coordinates */
    global.cv = 0;
            
    global.umin = 0;
    global.umax = 80;
    global.vmin = 0;
    global.vmax = 24;

    global.lastline = lastline; 

    buff.row  = malloc(1*sizeof(char));
    buff.size = 1;

  
}




int inWindow(int ix, int iy) 
{
  
    int xmin = global.xmin;    /* window edges in text coordinates */
    int ymin = global.ymin;
    int xmax = global.xmax;
    int ymax = global.ymax;

    int testa = (ix >= xmin) && (ix <= xmax); 
    int testb = (iy >= ymin) && (iy <= ymax);
  
    return testa && testb;     /* returns true inside the window   */

}



int main(int argc, char** argv)
{

  init(argc, argv);

  while (1) 

   {
    int retval = ReadKey();

    edal(retval, global.iy);

    setWindow();

    window(global.xmin,global.xmax,
           global.ymin,global.ymax);
   }

  return 0; // this statement is never reached
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

int ReadKey() 
{
  char c; int nread;

  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) 
  if (nread == -1 && errno != EAGAIN) die("terminated in readkey");
  else ; // write(STDIN_FILENO,"*",1); 
  write(STDOUT_FILENO,"\n\r",2);
 
  if (c == (char) CTRL_Q) die("exiting at CTRL_q");  // CTRL-q is 17 in decimal

  if (c != 27) return c; 

  
  char seq[3]={' ',' ',' '}; int count = 1;
  for (int n = 0; n < 3; ++n) 
   {if (read(STDIN_FILENO, &seq[n], 1) == 1) {count++;}
    else break;}

  int retval;
  if (count > 1) retval = encode(count, seq);

  return retval;
}


//            implement scrolling
// setWindow  Set Boundary Parameters for display window
//            

void setWindow(void)
{

    int ix,iy;                 /* insertion point, text coordinates */
    int lastline;              /* last line (max iy) in text            */

    int xmin,xmax,ymin,ymax;   /* window edges in text coordinates      */ 
    int umin,umax,vmin,vmax;   /* window edges in screen coordinates    */

    int cu,cv;                 /* cursor position in screen coordinates */

    lastline = global.lastline;
    ix = global.ix;
    iy = global.iy;
    possibleIxIy;

    xmin = global.xmin;
    xmax = global.xmax;
    ymin = global.ymin;
    ymax = global.ymax;

    int ysize; if (lastline < 20) ysize = lastline;
               else               ysize = 20;

    if (ix > xmax)  {xmax = ix; xmin = xmax - 79;}
    if (ix < xmin)  {xmin = ix; xmax = xmin + 79;}
    if (iy > ymax)  {
                     ymax = iy;    ymin = ymax - ysize;
                     if (ymin < 0) ymin = 0; 
                    }
//    writeToScreen("ix = ");writeDigit(ix,1);writeToScreen("\n\r");
//    writeToScreen("iy = ");writeDigit(iy,1);writeToScreen("\n\r");
//    writeToScreen("ymax = ");writeDigit(ymax,1);writeToScreen("\n\r");
//    writeToScreen("ymin = ");writeDigit(ymin,1);writeToScreen("\n\r");
//    writeToScreen("xmax = ");writeDigit(xmax,1);writeToScreen("\n\r");
//    writeToScreen("xmin = ");writeDigit(xmin,1);writeToScreen("\n\r");

    global.xmin = xmin;
    global.xmax = xmax;
    global.ymin = ymin;
    global.ymax = ymax;

    global.cu = global.ix - global.xmin;
    global.cv = global.iy - global.ymin;


    int testa = inAline(global.ix,global.iy);
    int testb = inWindow(global.ix,global.iy);

    if (!testa) die("testa:exiting in setWindow.c");
    if (!testb) die("testb:exiting in setWindow.c");

}
void window(int xmin, int xmax, int ymin, int ymax)
{

    writeToScreen(CursorHide);
    writeToScreen(ClearScreen);
    writeToScreen(CursorToTopLeft);

    int y; int count = 0;

    for (y = ymin; y <= ymax; y++) 
  {
    if (y > global.lastline) break;
    char *s = xmin + text[y].row; 

    int no;
    for ( no = 0; no + xmin <= xmax; no++)     
    {
    if (no==text[y].size) {break;}; 
    if (*s == '\n')        {break;};
    write(STDOUT_FILENO,s,1); s++; count++;
    }
    write(STDOUT_FILENO,"\n\r",2);
  }

    writeToScreen(CursorToTopLeft);
    int no; 
    for ( no = 0; no < global.cu ; no ++ ) writeToScreen(CursorForward);
    for ( no = 0; no < global.cv ; no ++ ) writeToScreen(CursorDown);
    writeToScreen(CursorDisplay);
}

void writeDigit(int digit,int fildes)
{
  char buf[20];
   snprintf(buf,4,"%d\0",digit);
   write(fildes,buf,strlen(buf));
}

