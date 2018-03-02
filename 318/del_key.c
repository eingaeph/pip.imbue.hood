
// delete key action

void del_key(int fetch)
{

  int size = text[fetch].size;
  int limit = size - 1;
   
  if (size == 0) 
    {
     assert(text[fetch].row == NULL);
     global.ix = 0;
     text[fetch].row = NULL;
     return;
    }

  if (size == 1)
    {
     global.ix = 0;
     if (text[fetch].row != NULL); free(text[fetch].row); 
     text[fetch].row = NULL;
     return;
    }
     
  assert(text[fetch].size > 1);
 
  char *new;

  new = malloc((limit)*sizeof(char));

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


  if      (global.ix >= limit) global.ix = limit - 1;
  else if (global.ix <= 0)     global.ix = 0;



  possibleLine;

  return;

}

