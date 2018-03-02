
// delete key action

void del_key(int fetch)
{

  int limit = text[fetch].size - 1 ; 
  char *new;
  if (limit > 0) new = malloc((limit)*sizeof(char));
  else           new = NULL;

  char *chng = new;
  char *orig = text[fetch].row;

  int no; 
  for (no = 0 ; no <= limit; no++)
    {
     if (no != global.ix)  {*chng = *orig; chng++; orig++;}
     else                  { orig++ ;} // skipping
    }

  if (text[fetch].row != NULL); free(text[fetch].row); 
  text[fetch].row = new; text[fetch].size = limit; 

  if (global.ix >= limit) global.ix = limit - 1;
  if (global.ix <= 0)     global.ix = 0;

  possibleLine;

  return;

}

