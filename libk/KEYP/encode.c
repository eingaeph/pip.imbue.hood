#include "../libk.h"

// handle keyboard stream escape sequences.
// encode multi-character escape sequences as a full word integer

int encode (int count, char* seq)
{

// testa, testb, testc determine the cases handled by encode 
  int testa = ( (seq[0] == '[')); 
  int testb = ( (count < 4 ) );
  int testc = ( (seq[2] == '~') );
// return ESC is the default (to handle unusual cases)
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
// return ESC is the default (to handle unusual cases)     
  return ESC; // this is unusual 
}


