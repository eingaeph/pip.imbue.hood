void sear(void)
{


    int y;

    writeToScreen(CursorHide);
    writeToScreen(ClearScreen);

/*** construct a haystack to contain the line ***/

    for (y = 0; y <= global.lastline; y++) 
  {
    if (text[y].size == 0) continue;

    char *haystack;      //build a null terminated string here 
    char *needle   = "story";
    char *ptr;

    if (text[y].size == 0) continue;

    haystack = malloc((text[y].size + 1)*sizeof(char));

    memcpy(haystack,text[y].row,text[y].size);
       
/*** search for needle ***/

    ptr = strstr(haystack,needle); 

    if (ptr != NULL) {
                       writeToScreen("foundit ! "); writeDigit(y,1); 
                       writeToScreen("    ");
                       write(1,text[y].row,text[y].size); 
                       writeToScreen("\n\r");
                     } 
    free(haystack);

  }

    writeToScreen(CursorToTopLeft);
    writeToScreen(CursorDisplay);

  exit(0);
}
