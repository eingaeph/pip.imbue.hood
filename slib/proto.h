
/* 127.c */

int  encode(int count, char *seq);

  //  if (read(STDIN_FILENO, &seq[0], 1) == 1) {count++;}
  //  if (read(STDIN_FILENO, &seq[1], 1) == 1) {count++;}
  //  if (read(STDIN_FILENO, &seq[2], 1) == 1) {count++;}

  //  if (count > 1) {int ignore = encode(count,seq);}

void die(const char *s);

  //  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
  //   die("tcsetattr");

void disableRawMode(void);
void enableRawMode(void);

  // enableRawMode();

void writeDigit(int digit);
char ReadKey(void);

  //  while (1) {char c = ReadKey();}

int  getr(char **qtr);

  //  line.size = getr(&line.row); 

int  addAline(int here, int maxndx);
int  deleteAline(int omit, int maxndx);
void etxt(int maxndx);

  // maxndx = replaceAline(5,maxndx); etxt(maxndx);

int  replaceAline(int nsrt, int maxndx);

  // maxndx = replaceAline(5,maxndx); etxt(maxndx);
int  readAline(void);

  // for (numb = 0 ; numb < 100; numb++) 
  // {
  //  retval=readAline(); 
  //  if (nread == 0) {break;}
  //  lastline = line.count; 
  // }

