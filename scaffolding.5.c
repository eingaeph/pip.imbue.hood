
#include <string.h>
#include <unistd.h>
#include <termios.h>

/* ======================= Low level terminal handling ====================== */

static struct termios orig_termios; /* Save original struct termios */

void disableRawMode() {

     tcsetattr(STDOUT_FILENO, TCSAFLUSH, &orig_termios);
     return;
}

int enableRawMode(int fd) {
    struct termios raw;

    raw = orig_termios;  /* modify the original mode */
    /* input modes: no break, no CR to NL, no parity check, no strip char,
     * no start/stop output control. */
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    /* output modes - disable post processing */
    raw.c_oflag &= ~(OPOST);
    /* control modes - set 8 bit chars */
    raw.c_cflag |= (CS8);
    /* local modes - choing off, canonical off, no extended functions,
     * no signal chars (^Z,^C) */
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    /* control chars - set return condition: min number of bytes and timer. */
    raw.c_cc[VMIN] = 0; /* Return each byte, or zero for timeout. */
    raw.c_cc[VTIME] = 1; /* 100 ms timeout (unit is tens of second). */

    tcgetattr(fd, &orig_termios);
    tcsetattr(fd,TCSAFLUSH,&raw); 

    return 0;

}


/* VT100 Display Control Escape Sequences */

char ClearScreen[15]=                          "\x1b[2J";
char CursorToTopLeft[15] =                     "\x1b[H";
char TildeReturnNewline[15] =                  "~\r\n";

/*
two sequences
C is cursor foward, but don't exit the screen
B is cursor down, but don't exit the screen
999 is a large enough maximum number of steps
*/

char CursorToMaxForwardMaxDown[15]=           "\x1b[999C\x1b[999B";
char GetCursorPosition[15] =                  "\x1b[6n";

/*
the terminal reply to GetCursorPosition   "24;80R" or similar
*/

char CursorHide[15]=                          "\x1b[?25l";
char CursorDisplay[15]=                       "\x1b[?25h";
char ClearCurrentLine[15]=                    "\x1b[K";


int
main()
    {

     enableRawMode(STDIN_FILENO);
     size_t size = strlen(CursorToMaxForwardMaxDown);
     write(STDOUT_FILENO,&CursorToMaxForwardMaxDown, size);
     disableRawMode();

return 0;
}
