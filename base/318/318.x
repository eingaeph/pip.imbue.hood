#! /usr/bin/tcc -run

/***

   keypress wait intercept translate

***/

/*** includes ***/

#include <time.h>
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


#define possibleIxIy    assert( global.iy <= global.lastline);            \
                        assert( global.iy >= 0); assert( global.ix >= 0); \
                        assert( global.ix <= text[global.iy].size + 1 );


// invoke with      int testy = iy; possibleLine;
  
#define possibleLine    assert(       ((text[testy].row == NULL) &&       \
                                       (text[testy].size == 0  ))         \
                                 ||                                       \
                                      ((text[testy].row != NULL) &&       \
                                       (text[testy].size >  0  ))         \
                               ); 

#define testScreen      assert( global.xmin < global.xmax);            \
                        assert( global.xmin > 0 );                     \
                        assert( global.ymin < global.ymax);            \
                        assert( global.ymin >= 0 );                    \
                        assert( global.ymax) <= lastline + 1 );

#define writeToScreen(x)  write(STDOUT_FILENO,x,strlen(x))
#define wts(x)            write(STDOUT_FILENO,x,strlen(x));delay();

#define chekfree(x)     assert(x != NULL);                      \
                        free(x);

/*** global symbols ***/

struct termios orig_termios;

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

    int fpinp; 
    int fptra;
    int fpscp; 
    int nread;

    int noscript;

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

void possibleScreen(void);
void delay(void);
int  pageDown(void);
int  winOut(int y, int xmin, int xmax);
int  replay(void);
void sear(void);
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

  iy++; if(iy > lastline ) iy = lastline;

  int size = text[iy].size;
  if (size < ix + 1 )  ix = size - 1;
  if (size = 0) ix = 0;

//store the insertion point 

  global.ix   = ix;
  global.iy   = iy;

  return 0;

}



int arrow_up(void)
{

  int iy = global.iy; 
  int ix = global.ix;
  int ymax = global.ymax;
  int lastline = global.lastline;


  writeToScreen("arow iy =  ");writeDigit(global.iy,1);writeToScreen("       kkk\n\r");
  writeToScreen("arow ix =  ");writeDigit(global.ix,1);writeToScreen("       kkk\n\r");

  iy--; if(iy < 0 ) iy = 0;

  int size = text[iy].size;
  if (size < ix + 1 )  ix = size - 1;
  if (ix < 0 ) ix = 0;

//store the insertion point 

  global.ix   = ix;
  global.iy   = iy;

  writeToScreen("arow iy =  ");writeDigit(global.iy,1);writeToScreen("       lll\n\r");
  writeToScreen("arow ix =  ");writeDigit(global.ix,1);writeToScreen("       lll\n\r");

  return 0;

}

void buildScreenBuffer(int star, int stop)
{
}



// chin  character insert, printable

void chin(char c, int fetch)
{
  assert(global.iy == fetch);
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
  
  assert((text[fetch].row != NULL) || (text[fetch].size == 0));
  if (text[fetch].row != NULL) free(text[fetch].row); 
  text[fetch].row = new; 
  text[fetch].size = limit; 
  global.ix++; if(limit == 1) global.ix = 0;


  int testy = fetch; possibleLine;

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
void delay(void)
{
  clock_t ticks1, ticks2;

  ticks1=clock();
  ticks2=ticks1;
//  while((ticks2-ticks1) < 1234567)
  while((ticks2-ticks1) < 1034567)
         ticks2=clock();
}


void del_key(int fetch)
{
  possibleIxIy;
  int testy = fetch; possibleLine;
  int testa = (text[fetch].size == 0); // first edge case
  if (testa) {assert(global.ix == 0);   
              assert(text[fetch].row == NULL);
              return;}

  int testb = (text[fetch].size == 1); // second edge case
  if (testb) {free(text[fetch].row);
              text[fetch].row = NULL;
              text[fetch].size = 0;
              global.ix = 0; 
              return;}

  assert(text[fetch].size > 1); assert(text[fetch].row != NULL);

  int limit = text[fetch].size - 1 ; 
  char *new; new = malloc((limit)*sizeof(char));

  char *chng = new;
  char *orig = text[fetch].row;

  int no; 
  for (no = 0 ; no <= limit; no++)
    {
     if (no != global.ix)  {*chng = *orig; chng++; orig++;}
     else                  { orig++ ;} // skipping
    }

  free(text[fetch].row); 
  text[fetch].row = new; text[fetch].size = limit; 

  if (global.ix >= limit) global.ix = limit - 1;

  assert(global.ix >= 0);
  testy = fetch; possibleLine;

  return;

}

void die(const char *s) {
  writeToScreen(CursorDisplay);
//  writeToScreen(ClearScreen);
//  writeToScreen(CursorToTopLeft); 
//  perror(s);
  writeToScreen("\n\r");
  writeToScreen(ClearCurrentLine);
  writeToScreen(s); 
  writeToScreen("\n\r");
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

  assert(iy == fetch);

  int test = (retval > 31 && retval < 127); // true for printable character

  if (test)                             {chin(c,fetch); return 0;}     
  if (retval == BACKSPACE  & ix != 0)   {global.ix-- ;  return 0;}
  if (retval == ARROW_LEFT & ix != 0)   {global.ix-- ;  return 0;}
  if (retval == ARROW_RIGHT)            {global.ix++ ;  return 0;}
  if (retval == ARROW_UP   & iy != 0)   {arrow_up();    return 0;}
  if (retval == ARROW_DOWN )            {arrow_down();  return 0;}
  if (retval == ENTER)                  {enter();       return 0;}
  if (retval == CTRL_K)                 {delAline();    return 0;}
  if (retval == DEL_KEY)                {del_key(fetch);return 0;} 
  if (retval == HOME_KEY)               {global.ix = 0; return 0;} 
  if (retval == PAGE_DOWN)              {pageDown();    return 0;}

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
  int ix = global.ix;              // text x insertion point
  int iy = global.iy;              // text y insertion point
  int lastline = global.lastline;  // number of rows in text
  int lena = ix + 1;               // number of chars in newline firs
  int lenb = text[iy].size - lena; // number of chars in newline seco

  wts("entering enter.c    \n\r");
  int testy = iy; possibleLine;

  int testa = (text[iy].size == 0) ;
  if (testa) assert(ix = 0);
  if (testa) die("trying to enter a zero length line\n\r");

  assert(text[iy].size > 0);

/*** build firs and seco ***/

  char *firs;
  if (lena > 0) firs = malloc(lena*sizeof(char)); //string firs
  else          firs = NULL;                      //zero length
  char *seco; 
  if (lenb > 0) seco = malloc(lenb*sizeof(char)); //string seco
  else          seco = NULL;                      //zero length

  char *chng = firs; // populate firs length lena 
  char *orig = text[iy].row; 
  int no; for (no = 0 ; no < lena; no++)
    {*chng = *orig; chng++; orig++;}

  chng = seco;       // populate seco length lenb
  for (no = lena; no < lena + lenb; no++)
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


  if(text[iy].row != NULL); free(text[iy].row); 

  global.lastline ++; lastline = global.lastline; 
  global.ix = 0; global.iy++;

  wts("call realloc, expand text    \n\r");
  writeDigit(lastline,1); wts("    \n\r");

  text = realloc(text,(lastline+2)*sizeof(slot));
  for (j = 0; j <= lastline; j++) {text[j] = new[j];writeDigit(j,1);wts("\n\r");}

  if (new != NULL); free(new);

}
int getCursorPosition(int *rows, int *cols) 
{
}

int getl(char **qtr)    // getline work-alike
{
  char inLine[240];     // sets maximum linesize at three times reasonable
  char* ptr;

  int inLineSize = 0; 
  char *s = &inLine[0];   //s and inLine are aliases of each other
  while((global.nread = read(global.fpinp,s,1))==1) 
    {if (*s != '\n') {s++; inLineSize++;} else break;}

  if (inLineSize == 0) {ptr = NULL; *qtr = ptr; return inLineSize;}

  ptr = malloc(inLineSize*sizeof(char));
  memcpy(ptr,inLine,inLineSize);
  *qtr = ptr;

  return inLineSize;
}



void init(int argc, char** argv)
{
    int numb; int retval; int lastline;
    char *outt;

    if(argc < 2) die("filename not entered as argument");

    enableRawMode();

    char * filename = argv[1];
    write(STDOUT_FILENO,filename,strlen(filename)); 
    write(STDOUT_FILENO,"\n\r",2);

    display = malloc(     (60)*sizeof(slot));

    global.fpinp = open(filename,O_RDONLY);
    global.fptra = open("/dev/pts/18", O_RDWR);
//    global.fpscp = open("script",O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);

   for (numb = 0 ; numb < 100; numb++) 
    {
     retval=readAline();
     if (global.nread == 0) {break;}
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

    global.noscript = 0;

    buff.row  = malloc(1*sizeof(char));
    buff.size = 1;
  
}





int main(int argc, char** argv)
{

  init(argc, argv);

  while (1) 

   {

    int testa = 1; int retval; testa = 0;

    if (testa) retval = replay();
    else       retval = ReadKey(); 


    int testb = (retval != CTRL_U);

    if (testb)
      {
        edal(retval, global.iy);

        setWindow();
 
        window(global.xmin,global.xmax,
               global.ymin,global.ymax);
      }

    else sear();
  
   }

  return 0; // this statement is never reached
}


int pageDown(void)
{

// delta = ymax - ymin 

  int delta = 24;

// default action

   global.ymax = global.ymax + delta;
   global.ymin = global.ymin + delta;
   global.iy = global.ymin; global.ix = 0;

// edge cases 

   if(global.ymax > global.lastline) 
     {
      global.ymax = global.lastline;
      global.ymin = global.lastline - delta;
      global.ix = 0;
      global.iy = global.ymin;
     }
  
  if(global.ymin < 0) 
    {
     global.ymin = 0; 
     global.iy = 0;
     global.ix = 0;
    }

                         possibleIxIy;
  int testy = global.iy; possibleLine;

  return 0;

}

void possibleScreen(void)
{
  int ymin = global.ymin;
  int ymax = global.ymax;
  int y;

  for (y = ymin; y <= ymax; y++)
    {
     assert(text[y].size >= 0 );
     assert(text[y].size < 200); 
     if(text[y].row == NULL) assert(text[y].size == 0);
     if(text[y].size == 0)   assert(text[y].row  == NULL);
    }
}
int readAline(void)
{
    line.row = NULL; 
    line.size = getl(&line.row);  

    if (line.size == 0) { 
                         text[line.count].size = line.size; 
                         text[line.count].row  = NULL;
                         line.count++;
                         return line.size;
                        }

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

int replay(void)
{
  clock_t ticks1, ticks2;

  ticks1=clock();
  ticks2=ticks1;
  while((ticks2-ticks1)<1034567)
         ticks2=clock();

 int store[200]; char c; int retval;

 int j = 1;

          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;          
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;          
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_RIGHT;j = j + 1;
          store[j] = ARROW_RIGHT;j = j + 1;
          store[j] = ARROW_RIGHT;j = j + 1;
          store[j] = ARROW_RIGHT;j = j + 1;
          store[j] = ARROW_UP;   j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
 c = 'a'; store[j] = c; j = j + 1;  
 c = 'b'; store[j] = c; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
 c = 'c'; store[j] = c; j = j + 1;
 c = 'd'; store[j] = c; j = j + 1;
          store[j] = ENTER;      j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_UP;   j = j + 1;
          store[j] = ARROW_UP;   j = j + 1;
          store[j] = ARROW_UP;   j = j + 1;
          store[j] = ARROW_UP;   j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;


 global.noscript++;
 if (global.noscript < j) retval = store[global.noscript];
 else die("ending in function replay");

//  printf("The wait time is %ld ticks.\n",ticks2-ticks1);
//  printf("This value of CLOCKS_PER_SEC is %d.\n",CLOCKS_PER_SEC);

  return retval;

}
void sear(void)
{


    int y;

    writeToScreen(CursorHide);
    writeToScreen(ClearScreen);

/*** construct a haystack to contain the line ***/

    for (y = 0; y <= global.lastline; y++) 
  {
    if (text[y].size == 0) continue;

    char *haystack;      //build a null terminated string here 
    char *needle   = "story";
    char *ptr;

    if (text[y].size == 0) continue;

    haystack = malloc((text[y].size + 1)*sizeof(char));

    memcpy(haystack,text[y].row,text[y].size);
       
/*** search for needle ***/

    ptr = strstr(haystack,needle); 

    if (ptr != NULL) {
                       writeToScreen("foundit ! "); writeDigit(y,1); 
                       writeToScreen("    ");
                       write(1,text[y].row,text[y].size); 
                       writeToScreen("\n\r");
                     } 
    free(haystack);

  }

    writeToScreen(CursorToTopLeft);
    writeToScreen(CursorDisplay);

  exit(0);
}

//            implement scrolling
// setWindow  Set Boundary Parameters for display window
//            

void setWindow(void)
{

//    int ix,iy;                 /* insertion point, text coordinates */
//    int lastline;              /* last line (max iy) in text            */

//    int xmin,xmax,ymin,ymax;   /* window edges in text coordinates      */ 
//    int umin,umax,vmin,vmax;   /* window edges in screen coordinates    */

//    int cu,cv;                 /* cursor position in screen coordinates */

    possibleIxIy;

    int ysize; if (global.lastline < 20) ysize = global.lastline;
               else                      ysize = 20;

    if (global.ix > global.xmax)  {global.xmax = global.ix; global.xmin = global.xmax - 79;}
    if (global.ix < global.xmin)  {global.xmin = global.ix; global.xmax = global.xmin + 79;}
    if (global.iy > global.ymax)  
                  {
                       global.ymax = global.iy;    
                       global.ymin = global.ymax - ysize;
                   if (global.ymin < 0) global.ymin = 0; 
                  }

    global.cu = global.ix - global.xmin;
    global.cv = global.iy - global.ymin;

    int testy = global.iy; possibleLine;

}
void window(int xmin, int xmax, int ymin, int ymax)
{

    writeToScreen(CursorHide);
    writeToScreen(ClearScreen);
    writeToScreen(CursorToTopLeft);

    int y; int count = 0;

//    wts("drawing the window \n\r");

    possibleScreen();

    for (y = ymin; y <= ymax; y++) 
   {
     if (y > global.lastline) break;

     assert(!(text[y].size > 0 && text[y].row == NULL));
     if(text[y].row == NULL) {write (STDOUT_FILENO,"\n\r",2);
                              continue; }

    char *s = xmin + text[y].row; 

    int no;
    for ( no = 0; no + xmin <= xmax; no++)
    {
    if (no==text[y].size) {break;};
    if (*s == '\r')       {break;};
    if (*s == '\n')       {break;};
    write(STDOUT_FILENO,s,1); s++; count++;
    }
    write(STDOUT_FILENO,"\n\r",2);
   }

//    wts("placing the cursor \n\r");

    writeToScreen(CursorToTopLeft);
    int no; 
    for ( no = 0; no < global.cu ; no ++ ) writeToScreen(CursorForward);
    for ( no = 0; no < global.cv ; no ++ ) writeToScreen(CursorDown);
    writeToScreen(CursorDisplay);

}
int winOut(int y, int xmin, int xmax)
{

/*** write the line ***/

  int delta = 0;
  assert(text[y].row != NULL);

  char *s = xmin + text[y].row; 

  int no;
    for ( no = 0; no + xmin <= xmax; no++)     
    {
     if (no==text[y].size)  {break;}; 
     if (*s == '\n')        {break;};
     write(STDOUT_FILENO,s,1); s++; delta++;
    }
  
  return delta;
}

void writeDigit(int digit,int fildes)
{
  char buf[20];
   snprintf(buf,4,"%d\0",digit);
   write(fildes,buf,strlen(buf));
}

