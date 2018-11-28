// allibs   libraries required to build libk

#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <time.h>

// FIND

#define _GNU_SOURCE 

void *memmem(const void *haystack, size_t haystacklen, const void *needle, size_t needlelen);
void callWind(int cu, int cv);
void moda(int retval);
void modb(int retval);

// XLIN

void enter(void);
void xline(int iy, char* firs, int lena, char *seco, int lenb);

//REPL

void delay(void);
void draw(void);
void init(int argc, char** argv);
int replay(void);
void waiter(int iw);

//EDAL

struct { int xmin; int xmax; int ymin; int ymax; } arg2;

#define possibleLine    assert(       ((text[(glob.iy)].row  == NULL) &&       \
                                       (text[(glob.iy)].size == 0  ))          \
                                 ||                                            \
                                      ((text[(glob.iy)].row  != NULL)  &&      \
                                       (text[(glob.iy)].size  >  0  ))         \
                               );


#define possibleIxIy    assert( glob.iy < glob.numbLines);            \
                        assert( glob.iy >= 0); assert( glob.ix >= 0); \
                        assert( glob.ix <= text[glob.iy].size);


int arrow_down(void);
void arrow_left(void);
void arrow_right(void);
int arrow_up(void);
void backspace(void);
void chin(char c, int fetch);
void del_key(int fetch);
int editAline(int retval, int fetch);
int end_key(void);
int pageDown(void);
int pageUp(void);
void setWindow(void);

// WARF

/* global vars */

typedef struct {ssize_t size; char *row; int count;}   slot;

    slot line;
    slot *text;

    size_t linecap;
    FILE *fp;

int readAfile(char *filename);
int readAline(void);
void wind(int xmin, int xmax, int ymin, int ymax, int lastline);

// KEYP

int  ReadKey(void);
void die(const char *s);
int  encode (int count, char* seq);

// UVSE

void enableRawMode(void);
void disableRawMode(void);
int  getCursorPosition(int* rows, int* cols);
void screenTest(void);
void uvset(void);

typedef struct 
{

    int rows,cols;             /* window rows 1...rows, cols 1...cols */
    int x,y;                   /* char no, line no, text coordinates */
    int ix,iy;                 /* insertion point, text coordinates */

    int xmin,xmax,ymin,ymax;   /* window edges in text coordinates  */ 

    int u,v;                   /* char no, line no */
    int cu,cv;                 /* cursor position in screen coordinates */

    int umin,umax,vmin,vmax;   /* window edges in screen coordinates */

    int numbLines;             /* number of lines in text */

} global;

global glob;

struct termios orig_termios;

#include "/data.base/product/libk/VT100.h"
#include "/data.base/product/libk/keyvals.h"


