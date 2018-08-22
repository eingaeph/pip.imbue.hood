/*** VT100 Display Control Escape Sequences ***/

#define ClearScreen                          "\x1b[2J"
#define CursorToTopLeft                      "\x1b[H"
#define TildeReturnNewline                   "~\r\n"

#define ReturnNewline                        "\r\n"
#define CursorUp                             "\x1b[1A"
#define CursorDown                           "\x1b[1B"
#define CursorForward                        "\x1b[1C"
#define CursorBack                           "\x1b[1D"

/*
two sequences
C is cursor foward, but don't exit the screen
B is cursor down, but don't exit the screen
999 is a large enough maximum number of steps
*/

#define CursorToMaxForwardMaxDown           "\x1b[999C\x1b[999B"
#define CursorToMaxLeft                     "\x1b[999D"
#define GetCursorPosition                   "\x1b[6n"

/*
the terminal reply to GetCursorPosition   "24;80R" or similar
*/

#define CursorHide                          "\x1b[?25l"
#define CursorDisplay                       "\x1b[?25h"
#define ClearCurrentLine                    "\x1b[K"
#define CursorToCenter                      "\x1b[12;30f"

//Force Cursor Position	<ESC>[{ROW};{COLUMN}f

