
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

void enableRawMode(void);
void disableRawMode(void);
int  getCursorPosition(int* rows, int* cols);
void screenTest(void);
void uvset(void);
