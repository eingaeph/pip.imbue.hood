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

void xline(int iy, char *firs, int lena, char *seco, int lenb);
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

