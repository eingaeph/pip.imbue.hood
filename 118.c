#! /usr/bin/tcc -run

/***
   init readAline
   keypress wait intercept
   keypress code translater
   e
   getCursorPosition
   buildScreenBuffer

***/

/*** includes ***/

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h> //open,close per Kerrisk page 72
#include <fcntl.h>    //open,close 

/*** global symbols ***/

struct termios orig_termios;

struct {int fpinp; int nread; int fptra; } iovars;

typedef struct {ssize_t size; char *row; int count;} slot;

    slot line;  // set in readAline
    slot buff;  // set in edal
    slot *text;
    slot *display;

struct 
{

    int x,y;                   /* char no, line no, text coordinates */
    int ix,iy;                 /* insertion point, text coordinates */

    int xmin,xmax,ymin,ymax;   /* window edges in text coordinates  */ 

    int u,v;                   /* char no, line no */
    int cu,cv;                 /* cursor position in screen coordinates */

    int umin,umax,vmin,vmax;   /* window edges in screen coordinates */

} cord;

/*** Numeric Codes for Escape Sequences ***/

enum KEY_ACTION
{
        KEY_NULL = 0,       /* NULL */
        CTRL_C = 3,         /* Ctrl-c */
        CTRL_D = 4,         /* Ctrl-d */
        CTRL_F = 6,         /* Ctrl-f */
        CTRL_H = 8,         /* Ctrl-h */
        TAB = 9,            /* Tab */
        CTRL_L = 12,        /* Ctrl+l */
        ENTER = 13,         /* Enter */
        CTRL_Q = 17,        /* Ctrl-q */
        CTRL_S = 19,        /* Ctrl-s */
        CTRL_U = 21,        /* Ctrl-u */
        ESC = 27,           /* Escape */
        BACKSPACE =  127,   /* Backspace */

        /* The following are just soft codes, not really reported by the
         * terminal directly. */

        ARROW_LEFT = 1000,
        ARROW_RIGHT,
        ARROW_UP,
        ARROW_DOWN,
        DEL_KEY,
        HOME_KEY,
        END_KEY,
        PAGE_UP,
        PAGE_DOWN,
        INSERT_KEY
};

/*** function declarations ***/

int readAline(void);
char encode (int count, char* seq);

void writeDigit(int digit);

/*** function definitions ***/

void wind(int xmin, int xmax, int ymin, int ymax)
{
 
    int y;
    for (y = ymin; y < ymax + 1; y++) 
    {
    char *s = xmin + text[y].row; 

    int no;
    for ( no = 0; no + xmin < xmax + 1; no++)     
    {
    if (no>text[y].size ) {break;}; 
    if (*s == '\n')       {break;};
    printf("%c",*s); s++;
    }
    printf("\n");
    }
}

void die(const char *s) {
  write(STDOUT_FILENO, "\x1b[2J", 4);
  write(STDOUT_FILENO, "\x1b[H", 3);

  perror(s);
  exit(1);
}

char ReadKey() 
{
  char c; int nread;
  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) 
  if (nread == -1 && errno != EAGAIN) die("terminated in readkey");

  char mesg[] = "readkey at work \n";
  write(STDOUT_FILENO,mesg,strlen(mesg));

  if (c == 17) write(STDOUT_FILENO,"\r\n",2); // CTRL-q 
  if (c == 17) exit(0);

  if (c != 27) return c; 

  char seq[3]={' ',' ',' '}; int count = 1;
  for (int n = 0; n < 3; ++n) 
   {if (read(STDIN_FILENO, &seq[n], 1) == 1) {count++;}
    else break;}

  if (count > 1) c = encode(count, seq);

  return c;
}

/*** handle escape sequences. ***/

char encode (int count, char* seq)
{
  write(1,"encode at work  ",16);
  write(1,"count = ",8);
  writeDigit(count);
  write(1,"  ",2);

  char buf[] = "   ";

  buf[0] = seq[0] ; write(STDOUT_FILENO,buf,1); 
  buf[0] = seq[1] ; write(STDOUT_FILENO,buf,1); 
  buf[0] = seq[2] ; write(STDOUT_FILENO,buf,1); 
  write(1,"\n\r",2);

  int testa = ( (seq[0] == '[')); 
  int testb = ( (count < 4 ) );
  int testc = ( (seq[2] == '~') );

  if (count < 3 ) return ESC;  // this is unusual
   
  if (!testa)     return ESC;

  if (testb) {
     switch(seq[1]) {
        case 'A': return ARROW_UP;
        case 'B': return ARROW_DOWN;
        case 'C': return ARROW_RIGHT;
        case 'D': return ARROW_LEFT;
        case 'H': return HOME_KEY;
        case 'F': return END_KEY;                            }
              }

  if (testc) {
     switch(seq[1]) {
        case '2': return INSERT_KEY;
        case '3': return DEL_KEY;
        case '5': return PAGE_UP;
        case '6': return PAGE_DOWN;
                    }
             } // else return ESC;  
     
  return ESC; // this is unusual 
}

void writeDigit(int digit)
{
  char buf[20];
   snprintf(buf,4,"%d",digit);
   write(STDOUT_FILENO,buf,4);
   return;
}

int edal(char c, int fetch)
{
  int fpt = iovars.fptra;
  free(buff.row);  // free space initialized in init or in this function
  buff.row = text[fetch].row;buff.size = text[fetch].size;
  // int insertionPoint = cord.ix; 

  char ClearScreen[]= "\x1b[2J"; write(fpt, ClearScreen,4);
  write(fpt,buff.row,buff.size); write(fpt,"\n",1);

  int test = (c > 31 && c < 127); // true for printable character
  if (c == ARROW_RIGHT) {cord.ix++ ; return 0;}
  if (!test) return 0;

  int limit = buff.size + 1 ; 
  char *chng = malloc((limit)*sizeof(char));
  char *save = chng;
  char *orig = buff.row;

  // "insert %c at position %d\n"

  int no;
  for (no = 0 ; no < limit; no++)
    {if (no != cord.ix)  {*chng = *orig; chng++; orig++;}
     else                {*chng = c; chng++;}
    }

  buff.row = save;    text[fetch].row = buff.row;
  buff.size = limit;  text[fetch].size = buff.size;

  write(fpt,buff.row,buff.size); write(fpt,"\n",1);

  char mesy[] = "eal is finished\n"; write(fpt,mesy,strlen(mesy));
  int ignore; read(STDIN_FILENO, &ignore, 1); // pause, wait for input 
  write(fpt, mesy, strlen(mesy));

  return 0;
}

void init(int argc, char** argv)
{
    int numb; int retval; int lastline;
    char *outt;

    if (argc == 1) return;

    char * filename = argv[1];
    write(STDOUT_FILENO,filename,strlen(argv[1])); write(1,"\n",1);

    display = malloc(     (60)*sizeof(slot));

    iovars.fpinp = open(filename,O_RDONLY);
    iovars.fptra = open("/dev/pts/18", O_RDWR);

    line.count = 0;
    for (numb = 0 ; numb < 100; numb++) 
    {
    retval=readAline(); 
    if (iovars.nread == 0) {break;}
    lastline = line.count; 

    }
   
    cord.ix = 0 ; 
    cord.iy = 0;    /* insertion point, text coordinates */

    cord.xmin =  0;
    cord.xmax = 79;
    cord.ymin =  0;
    cord.ymax = 23;   

    cord.cu = 0;    /*screen coordinates */
    cord.cv = 0;
            
    cord.umin = 1;
    cord.umax = 80;
    cord.vmin = 1;
    cord.vmax = 24;
    outt = "lastline = "; write(STDOUT_FILENO,outt,strlen(outt)); 
    writeDigit(lastline);  write(STDOUT_FILENO,"\n",1);

    buff.row  = malloc(1*sizeof(char));
    buff.size = 1;
}

int getl(char **qtr)    // getline work-alike
{
  char test[1];
  char inLine[240];     // sets maximum linesize at three times reasonable
  char* ptr;

  int nread; 
  int inLineSize = 0; 
  char *s = &inLine[0];   //s and inLine are aliases of each other
  while((iovars.nread = read(iovars.fpinp,s,1))==1) 
    {if (*s != '\n') {s++; inLineSize++;} else break;}

  if (inLineSize  > 0) {ptr = malloc(inLineSize*sizeof(char));
                        memcpy(ptr,inLine,inLineSize);
                       *qtr = ptr;}
  return inLineSize;
}

int readAline(void)
{
    line.row = 0; 
/***line.count (the number of lines read)***/ 
    line.size = getl(&line.row);    

    if (line.size == 0) {return line.size;}

    if((line.count == 0)) 
         { text = (slot *) malloc(     (1+line.count)*sizeof(slot));}
    else { text = (slot *)realloc(text,(1+line.count)*sizeof(slot));}

    char * ptr = malloc(line.size*sizeof(char));
    text[line.count].row = ptr  ;
    text[line.count].size = line.size;
    memcpy(ptr,line.row,line.size);  

    line.count++; 
    return line.size;
}

void buildScreenBuffer(int star, int stop)
{
//    printf("%s","buildScreenBuffer at work\n");

    for (int i=0; i<24; i++) {display[i].size  =   1;
                              display[i].row   = "~\n";
                              display[i].count =   0;}

    int dy = 0;
    display[0].row  = "kilo.c welcomes you";
    display[0].count = 0;
    display[0].size = strlen(display[0].row);

    dy = 1; int y = 0;
    display[dy].row  = text[y].row;
    display[dy].count = 0;
    display[dy].size = strlen(display[dy].row);   

    int i;  dy = 9;
    for (int i = star; i<(stop+1); i++)
         {dy++ ; display[dy] = text[i];}

    dy = -1 ;
    for (int i = 0; i< 22; i++) // make the limit 23 later
         {
          dy++ ;
          write(STDOUT_FILENO,display[dy].row,display[dy].size);
          write(STDOUT_FILENO,"\n",1);
         }

}


int getCursorPosition(int *rows, int *cols) {
  char buf[32];
  unsigned int i = 0;

  if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4) return -1;

  while (i < sizeof(buf) - 1) {
    if (read(STDIN_FILENO, &buf[i], 1) != 1) break;
    if (buf[i] == 'R') break;
    i++;
  }
  buf[i] = '\0';

  if (buf[0] != '\x1b' || buf[1] != '[') return -1;
  if (sscanf(&buf[2], "%d;%d", rows, cols) != 2) return -1;

  return 0;
}

void disableRawMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
  tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(disableRawMode);

  struct termios raw = orig_termios;
  raw.c_lflag &= ~(ECHO | ICANON);

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


int main(int argc, char** argv)
{

  init(argc, argv); enableRawMode();

  while (1) 
   {
    char c = ReadKey();

    edal(c,3);

//  buildScreenBuffer(5, 10);

    wind(0,79,0,9);

//  int x ; int y; getCursorPosition(&y, &x);
//  printf("x = %d, y = %d\n",x,y);

   }
  return 0;
}

