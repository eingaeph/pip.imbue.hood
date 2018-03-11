#! /usr/bin/tcc -run

/* Move cursor */

#include <string.h>
#include <unistd.h>

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
     
     size_t size = strlen(CursorToMaxForwardMaxDown);
     write(STDOUT_FILENO,&CursorToMaxForwardMaxDown, size);
                     
return 0;
}
