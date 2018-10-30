#include "../libk.h"

// function ReadKey
// read single and multi-byte characters 
// process multi-byte characters with encode 

int ReadKey() 
{
  char c; int nread;
  enableRawMode();
// Read one character (c) from standard input
  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) 
// if error in read 
  if (nread == -1 && errno != EAGAIN) die("terminated in readkey");
// if no erro write newline 
  else ; 
  write(STDOUT_FILENO,"\n\r",2);

// c != ESCAPE no further processing 

  if (c != 27) {disableRawMode();return c;}
// ESCAPE found 
// try to read a MultCharacter 
  char seq[3]={' ',' ',' '}; int count = 1;
  for (int n = 0; n < 3; ++n) 
   {if (read(STDIN_FILENO, &seq[n], 1) == 1) {count++;}
    else break;}

  int retval;
  if (count == 1) {retval = c; disableRawMode();return retval;}  
// return not executed invoke encode
                   retval = encode(count, seq);
  disableRawMode(); return retval;
}

