#! /usr/bin/tcc -run

#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

/* We define a very simple "append buffer" structure, that is an heap
 * allocated string where we can append to. This is useful in order to
 * write all the escape sequences in a buffer and flush them to the standard
 * output in a single call, to avoid flickering effects. */

struct abuf {
    char *b;
    int len;
};

#define ABUF_INIT {NULL,0}

void abAppend(struct abuf *ab, const char *s, int len) {
    char *new = realloc(ab->b,ab->len+len);

    if (new == NULL) return;
    memcpy(new+ab->len,s,len);
    ab->b = new;
    ab->len += len;
}

void abFree(struct abuf *ab) {
    free(ab->b);
}
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

/*  wrapper for abAppend */

void wrapa(struct abuf *ab, const char *s) 
{
    printf("wrappa processing <%s>\n",s);
    int len; len = (int) strlen(s);
    printf("length <%d>\n",len);
    abAppend(ab, s, len);   
}

/* VT100 Display Control Escape Sequences */

char ClearScreen[]=                          "\x1b[2J";
char CursorToTopLeft[] =                     "\x1b[H";
char TildeReturnNewline[] =                  "~\r\n";

char ReturnNewline[] =                       "\r\n";

/*
two sequences
C is cursor foward, but don't exit the screen
B is cursor down, but don't exit the screen
999 is a large enough maximum number of steps
*/

char CursorToMaxForwardMaxDown[]=           "\x1b[999C\x1b[999B";
char GetCursorPosition[] =                  "\x1b[6n";

/*
the terminal reply to GetCursorPosition   "24;80R" or similar
*/

char CursorHide[]=                          "\x1b[?25l";
char CursorDisplay[]=                       "\x1b[?25h";
char ClearCurrentLine[]=                    "\x1b[K";
char CursorToCenter[]=                      "\x1b[12;30f";

/* function main */
//Force Cursor Position	<ESC>[{ROW};{COLUMN}f
int
main()
    {
      int i;
      enableRawMode(STDIN_FILENO);

      struct abuf ab = ABUF_INIT;

      wrapa(&ab,ClearScreen); 
      char mocu[32]; int iter;
      for(iter = 8; iter < 16; iter ++) 
{
      snprintf(mocu,32,"\x1b[%d;%df",iter,30); wrapa(&ab,mocu);
                //wrapa(&ab,CursorToCenter);
      wrapa(&ab,"Hello world!");
}                                        
      wrapa(&ab,CursorToTopLeft);

for (i=1; i<25; i++) 
{
      wrapa(&ab,TildeReturnNewline);
}

      wrapa(&ab,CursorToTopLeft);

      char* filestring ="new";

 /* unlink filestring, if link exists */

      int ignore = unlink(filestring);

 /* Create filestring anew. Open filestring for writing.
   specify append, but this is unnecessary */

      int fd = open (filestring, O_WRONLY | O_CREAT | O_APPEND , 0666);

      int length = ab.len;
      write (fd, ab.b, length);

      close (fd);
        
      fwrite(ab.b , 1 , ab.len , stdout);
    
      abFree(&ab);
      disableRawMode();

      return 0;
}
