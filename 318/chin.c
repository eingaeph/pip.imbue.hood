
// chin  character insert, printable

void chin(char c, int fetch)
{
  assert(global.iy == fetch);
  wts("chin in operation \n\r");
  int limit = text[fetch].size + 1 ; 
  char *new = malloc((limit)*sizeof(char));
  char *chng = new;
  char *orig = text[fetch].row;

  int no; 
  for (no = 0 ; no < limit; no++)
    {
     if (no != global.ix)  {*chng = *orig; chng++; orig++;}
     else                  {*chng = c; chng++;}
    }
  
  assert((text[fetch].row != NULL) || (text[fetch].size == 0));
  if (text[fetch].row != NULL) free(text[fetch].row); 
  text[fetch].row = new; 
  text[fetch].size = limit; 
  global.ix++; if(limit == 1) global.ix = 0;

  possibleLine;

  return;

}

