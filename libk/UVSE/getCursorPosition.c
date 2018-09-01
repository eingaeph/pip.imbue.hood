#include "../libk.h"

int getCursorPosition(int *rows, int *cols)
{
    char buf[32];
    unsigned int i = 0;
    int ifd = STDIN_FILENO;
    int ofd = STDOUT_FILENO;

    /* Place Cursor */
    int lena = strlen( CursorToMaxForwardMaxDown );
    write(ofd, CursorToMaxForwardMaxDown, lena );
    /* Request cursor location */
    if (write(ofd, "\x1b[6n", 4) != 4) return -1;

    /* Read the response: ESC [ rows ; cols R */
    while (i < sizeof(buf)-1) {
        if (read(ifd,buf+i,1) != 1) break;
        if (buf[i] == 'R') break;
        i++;
    }
    buf[i] = '\0';

//  the terminal reply to GetCursorPosition   "24;80R" or similar
//    printf(" The screen returned <%s>\r\n",buf+2); fflush(stdout);

    /* Parse it. */
    int esc = 27;
    if (buf[0] != esc || buf[1] != '[') return -1;
    if (sscanf(buf+2,"%d;%d",rows,cols) != 2) return -1;

    return 0;
}
