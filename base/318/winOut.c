int winOut(int y, int xmin, int xmax)
{

/*** write the line ***/

  int delta = 0;
  assert(text[y].row != NULL);

  char *s = xmin + text[y].row; 

  int no;
    for ( no = 0; no + xmin <= xmax; no++)     
    {
     if (no==text[y].size)  {break;}; 
     if (*s == '\n')        {break;};
     write(STDOUT_FILENO,s,1); s++; delta++;
    }
  
  return delta;
}
