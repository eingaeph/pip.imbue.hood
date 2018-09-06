// allibs   libraries required to build libk

#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

//MOCU

struct { int xmin; int xmax; int ymin; int ymax; } arg2;

#define possibleLine    assert(       ((text[(glob.iy)].row  == NULL) &&       \
                                       (text[(glob.iy)].size == 0  ))          \
                                 ||                                            \
                                      ((text[(glob.iy)].row  != NULL)  &&      \
                                       (text[(glob.iy)].size  >  0  ))         \
                               );


#define possibleIxIy    assert( glob.iy <= glob.numbLines);            \
                        assert( glob.iy >= 0); assert( glob.ix >= 0); \
                        assert( glob.ix <= text[glob.iy].size - 1 );

int arrow_up(void);
void arrow_right(void);
void arrow_left(void);
int arrow_down(void);
void backspace(void);
void chin(char c, int fetch); //fetch text[fetch].row
int editAline(int retval, int fetch);
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

/* global vars */

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


