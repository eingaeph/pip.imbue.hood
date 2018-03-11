void die(const char *s) {
  writeToScreen(CursorDisplay);
//  writeToScreen(ClearScreen);
//  writeToScreen(CursorToTopLeft); 
//  perror(s);
  writeToScreen(s); writeToScreen("\n\r");
  exit(1);
}

