#include "KEYP.h"

void die(const char *s) {
//  writeToScreen(CursorDisplay);
//  writeToScreen(ClearScreen);
//  writeToScreen(CursorToTopLeft); 
  perror(s);
  printf("\n\r");
//  writeToScreen("\n\r");
//  writeToScreen(ClearCurrentLine);
//  writeToScreen(s); 
//  writeToScreen("\n\r");
  exit(1);
}


