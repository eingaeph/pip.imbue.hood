//#include "../allib.h"

int  getCursorPosition(int ifd, int ofd, int *rows, int *cols);
int  arrow_down(void);
void arrow_left(void);
void backspace(void);
void setWindow(void);
int  editAline(int retval, int fetch);
void chin(char c, int fetch);
int  ReadKey(void);

struct 
{

    int x,y;                   /* char no, line no, text coordinates */
    int ix,iy;                 /* insertion point, text coordinates */

    int xmin,xmax,ymin,ymax;   /* window edges in text coordinates  */ 

    int u,v;                   /* char no, line no */
    int cu,cv;                 /* cursor position in screen coordinates */

    int umin,umax,vmin,vmax;   /* window edges in screen coordinates */

    int numbLines;             /* number of lines in text */

} glob;

// invoke with      int testy = iy; possibleLine;
  
#define possibleLine    assert(       ((text[testy].row == NULL) &&       \
                                       (text[testy].size == 0  ))         \
                                 ||                                       \
                                      ((text[testy].row != NULL) &&       \
                                       (text[testy].size >  0  ))         \
                               ); 


#define possibleIxIy    assert( glob.iy <= glob.numbLines);            \
                        assert( glob.iy >= 0); assert( glob.ix >= 0); \
                        assert( glob.ix <= text[glob.iy].size - 1 );

