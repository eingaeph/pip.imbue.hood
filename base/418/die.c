void die(const char *s) {
  writeToScreen(CursorDisplay);
//  writeToScreen(ClearScreen);
//  writeToScreen(CursorToTopLeft); 
//  perror(s);
  writeToScreen("\n\r");
//  writeToScreen(ClearCurrentLine);
  writeToScreen(s); 
  writeToScreen("\n\r");
  exit(1);
}

