/*** global variables ***/

    size_t linecap;
    int nread;
    extern struct { int fp; int nread; } nput;

typedef struct slot
{
    ssize_t size;
    char *row;
    int count;
}   slot;

    extern slot line;
    extern slot *text;

extern struct termios orig_termios;


/*** VT100 Display Control Escape Sequences ***/

extern char ClearScreen[];//=                          "\x1b[2J";
extern char CursorToTopLeft[];// =                     "\x1b[H";
extern char TildeReturnNewline[];// =                  "~\r\n";

extern char ReturnNewline[];// =                       "\r\n";

/*
two sequences
C is cursor foward, but don't exit the screen
B is cursor down, but don't exit the screen
999 is a large enough maximum number of steps
*/

extern char CursorToMaxForwardMaxDown[];//=           "\x1b[999C\x1b[999B";
extern char GetCursorPosition[];// =                  "\x1b[6n";

/*
the terminal reply to GetCursorPosition   "24;80R" or similar
*/

extern char CursorHide[];//=                          "\x1b[?25l";
extern char CursorDisplay[];//=                       "\x1b[?25h";
extern char ClearCurrentLine[];//=                    "\x1b[K";
extern char CursorToCenter[];//=                      "\x1b[12;30f";

//Force Cursor Position	<ESC>[{ROW};{COLUMN}f


