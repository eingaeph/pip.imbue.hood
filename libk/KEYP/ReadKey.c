#include "KEYP.h"

int ReadKey() 
{
  char c; int nread;
  enableRawMode();
  
  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) 
  if (nread == -1 && errno != EAGAIN) die("terminated in readkey");
  else ; // write(STDIN_FILENO,"*",1); 
  write(STDOUT_FILENO,"\n\r",2);
 
  if (c == (char) CTRL_Q) die("exiting at CTRL_q");  // CTRL-Q is 17 in decimal

  if (c != 27) {disableRawMode();return c;}

  
  char seq[3]={' ',' ',' '}; int count = 1;
  for (int n = 0; n < 3; ++n) 
   {if (read(STDIN_FILENO, &seq[n], 1) == 1) {count++;}
    else break;}

  int retval;
  if (count == 1) {retval = c; disableRawMode();return retval;}  
                   retval = encode(count, seq);
  disableRawMode(); return retval;
}
