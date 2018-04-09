
// chin  character insert, printable

void chin(char c, int fetch)
{
  assert(global.iy == fetch);

  int limit = text[fetch].size + 1 ; 
  char *new = malloc((limit)*sizeof(char));
  char *orig = text[fetch].row;

  int no; int mo = 0; 
  for (no = 0 ; no < limit; no++)
    {
     if (no != global.ix)  {new[no] = orig[mo];mo++;}
     else                  {new[no] = c; }
    }

// ssize_t write(int fd, void *buffer, size_t count);

  for (no = 0; no < limit; no++) write(1,&new[no], 1); wts("\n\r");
  for (no = 0; no+1 < limit; no++) write(1,&orig[no], 1); wts("\n\r");
  
  assert((text[fetch].row != NULL) || (text[fetch].size == 0));

  if (text[fetch].row != NULL) free(text[fetch].row); 
  text[fetch].row = new; 
  text[fetch].size = limit; 
  global.ix++; if(limit == 1) global.ix = 0;

  char *test = text[fetch].row;
  for (no = 0; no < limit; no++) write(1,&test[no], 1); wts("\n\r");


  int testy = fetch; possibleLine;
  return;

}

