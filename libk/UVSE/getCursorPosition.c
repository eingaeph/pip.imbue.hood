#include "../libk.h"

/* function getCursorPosition */
/* get Screen Size, int rows, int cols */

int getCursorPosition(int *rows, int *cols)
{
    char buf[32];
    unsigned int i = 0;
    int ifd = STDIN_FILENO;
    int ofd = STDOUT_FILENO;

/* Place the Cursor at the bottom right of the screen*/
    int lena = strlen( CursorToMaxForwardMaxDown );
    write(ofd, CursorToMaxForwardMaxDown, lena );
/* Request the cursor location */
    if (write(ofd, "\x1b[6n", 4) != 4) return -1;

/* expect a reply from the screen (the terminal) */

/* Read the response: 
  (Expect the pattern) ESC [ rows ; cols R */
    while (i < sizeof(buf)-1) {
        if (read(ifd,buf+i,1) != 1) break;
        if (buf[i] == 'R') break;
        i++;
    }
    if (buf[i]!='R') return -1;
// replace R in the buffer with to make a string
    buf[i] = '\0';

//  after skippint two characters
//  the pattern of terminal reply to message GetCursorPosition is
//    "24;80R" or similar    
//  test it with printf(" The screen returned <%s>\r\n",buf+2); fflush(stdout);

/* Parse the string in buf with sscanf */
    int esc = 27;
    if (buf[0] != esc || buf[1] != '[') return -1;
    if (sscanf(buf+2,"%d;%d",rows,cols) != 2) return -1;

    return 0;
}
