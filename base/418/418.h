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
#include <sys/stat.h>   //open,close per Kerrisk page 72
#include <fcntl.h>      //open,close 
#include <sys/ioctl.h>  //ioctl

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
                        assert( global.xmin >= 0 );                    \
                        assert( global.ymin < global.ymax);            \
                        assert( global.ymin >= 0 );                    \
                        assert( global.ymax <= global.lastline);       \
                                                                       \
                        assert( global.ymax >= global.iy);             \
                        assert( global.ymin <= global.iy);             \
                        assert( global.xmax >= global.ix);             \
                        assert( global.xmin <= global.ix);             \
                                                                       \
                        possibleScreen();


#define writeToScreen(x)  write(STDOUT_FILENO,x,strlen(x))
#define wts(x)            write(STDOUT_FILENO,x,strlen(x));            \
                          waiter(0004567);

#define chekfree(x)     assert(x != NULL);                      \
                        free(x);

#define ABUF_INIT {NULL,0}

/*** global symbols ***/

struct abuf {
    char *b;
    int len;
};

#define ABUF_INIT {NULL,0}

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
The following are returned from the keyboard as 
multi character escape squences 
not as a single (16 bit ascii encoded) character
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
char CursorToMaxDown[]=                     "\x1b[999B";
char CursorToBeginingOfLine[]=              "\x1b[999D";
char GetCursorPosition[] =                  "\x1b[6n";

/*
the terminal reply to GetCursorPosition   "24;80R" or similarARROW
*/

char CursorHide[]=                          "\x1b[?25l";
char CursorDisplay[]=                       "\x1b[?25h";
char ClearCurrentLine[]=                    "\x1b[K";
char CursorToCenter[]=                      "\x1b[12;30f";

//Force Cursor Position	<ESC>[{ROW};{COLUMN}f

/*** function declarations ***/

void abAppend(struct abuf *ab, const char *s, int len) ;
void abFree(struct abuf *ab) ;
int  arrow_down(void);
void arrow_left(void);
void arrow_right(void);
int  arrow_up(void);
void backspace(void);
void buildScreenBuffer(int star, int stop);
void chin(char c, int fetch);
void delAline(void);
void delay(void);
void del_key(int fetch);
void die(const char *s);
void disableRawMode(void);
int  edal(int retval, int fetch);
void enableRawMode(void);
int  encode(int count, char *seq);
int  end_key(void);
void enter(void);
int  getCursorPosition(int ifd, int ofd, int *rows, int *cols);
int  getWindowSize(int ifd, int ofd, int *rows, int *cols);
int  getl(char **qtr);
void init(int argc, char **argv);
int  main(int argc, char **argv);
int  pageDown(void);
int  pageUp(void);
void possibleScreen(void);
int  readAline(void);
int  ReadKey(void);
int  replay(void);
void sear(void);
void setWindow(void);
void statusBar(void);
void waiter(int iw);
void window(int xmin, int xmax, int ymin, int ymax);
int  winOut(int y, int xmin, int xmax);
void writeDigit(int digit, int fildes);
void xline(int iy, char *firs, int lena, char *seco, int lenb);


/*** function definitions ***/

