/*** handle escape sequences. ***/

#include <unistd.h>
#include <termios.h>
#include "globvars.h"
#include "proto.h"

int encode (int count, char* seq)
{
  write(1,"encode at work  ",16);
  write(1,"count = ",8);
  writeDigit(count);
  write(1,"  ",2);

  char buf[] = "   ";
//  writeDigit(seq[0]);
  buf[0] = seq[0] ; write(STDOUT_FILENO,buf,1); 
  buf[0] = seq[1] ; write(STDOUT_FILENO,buf,1); 
  buf[0] = seq[2] ; write(STDOUT_FILENO,buf,1); 
  write(1,"\n\r",2);


  int testa = ( (seq[0] == '['));   
  int testb = ( ( testa ) && (seq[1] >= '0') && (seq[1] <='9') );
  int testc = ( ( testb ) && (count < 4 ));
  int testd = ( ( testb ) && (seq[2] == '~') );
   

  if (testa) write(1,"testa = TRUE\n\r",14);
  if (testb) write(1,"testb = TRUE\n\r",14);
  if (testc) write(1,"testc = TRUE\n\r",14);
  if (testd) write(1,"testd = TRUE\n\r",14);
  
  if (count < 3 ) return ESC;
  
  return ESC;
}
/*
  if (seq[0] == '[') 
     {
      if (seq[1] >= '0' && seq[1] <= '9') 
            {
             // Extended escape, read additional byte. 
             if (count  == 3) return ESC;
             if (seq[2] == '~') 
                {
                 switch(seq[1]) {
                 case '3': return DEL_KEY;
                 case '5': return PAGE_UP;
                 case '6': return PAGE_DOWN;
                                }
                 }
             else {
             switch(seq[1]) {
                 case 'A': return ARROW_UP;
                 case 'B': return ARROW_DOWN;
                 case 'C': return ARROW_RIGHT;
                 case 'D': return ARROW_LEFT;
                 case 'H': return HOME_KEY;
                 case 'F': return END_KEY;
                             }
                  }
            }
}

            // ESC O sequences. 
            else if (seq[0] == 'O') {
                switch(seq[1]) {
                case 'H': return HOME_KEY;
                case 'F': return END_KEY;
                }
            }
            break;
        default:
            return c;
        }
    }
}

*/
