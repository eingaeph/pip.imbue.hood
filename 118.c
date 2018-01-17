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
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h> //open,close per Kerrisk page 72
#include <fcntl.h>    //open,close 

/*** global symbols ***/

struct termios orig_termios;

struct { int fpinp; int nread; int fptra; } iovars;

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

/*** function declarations ***/

int readAline(void);

/*** function definitions ***/

void writeDigit(int digit)
{
  char buf[20];
   snprintf(buf,4,"%d",digit);
   write(STDOUT_FILENO,buf,4);
   return;
}

int edal(char c)
{
  write(iovars.fptra,&c,1);
  char msg[] = " was passed to eal\n";
  write(iovars.fptra,msg,strlen(msg));

//  buff.row = text[0].row;
//  buff.size = text[0].size;
//  write(iovars.fptra,buff.row,buff.size); 
//  write(iovars.fptra,"\n",1);
  
  int ignore; read(STDIN_FILENO, &ignore, 1); // pause, wait for input 

  char mesy[] = "eal is finished\n";
  write(iovars.fptra,mesy,strlen(mesy));

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
  init(argc, argv);

  enableRawMode();

  char c;
  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
    if (iscntrl(c)) {
      printf("%d\n", c);
    } else {
      printf("%d ('%c')\n", c, c);
    }

  edal(c);

 /* Build Screen Buffer */

  buildScreenBuffer(5, 10);


 /* Query screen for cursor location */

  int x ; int y; getCursorPosition(&y, &x);
//  printf("x = %d, y = %d\n",x,y);

  }

  return 0;
}

