/* VT100 Display Control Escape Sequences */

char ClearScreen =                         "\x1b[2J"
char CursorToTopLeft =                     "\x1b[H"
char TildeReturnNewline =                  "~\r\n"

/*
two sequences
C is cursor foward, but don't exit the screen
B is cursor down, but don't exit the screen
999 is a large enough maximum number of steps
*/

char CursorToMaxFowardMaxDown =           "\x1b[999C\x1b[999B"
char GetCursorPosition =                  "\x1b[6n"

/*
the terminal reply to GetCursorPosition   "24;80R" or similar
*/

char CursorHide =                         "\x1b[?25l"
char CursorDisplay =                      "\x1b[?25h"
char ClearCurrentLine                     "\x1b[K"

