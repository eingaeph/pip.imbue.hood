void die(const char *s) {
  writeToScreen(CursorDisplay);
//  writeToScreen(ClearScreen);
//  writeToScreen(CursorToTopLeft); 
//  perror(s);
  wts("\n\r");
  wts(ClearCurrentLine);wts(s); wts("\n\r");
  exit(1);
}

