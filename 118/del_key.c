
// chin  character insert, printiable

void del_key(int fetch)
{

  int limit = text[fetch].size - 1 ; 
  char *new = malloc((limit)*sizeof(char));
  char *chng = new;
  char *orig = text[fetch].row;

  int no; 
  for (no = 0 ; no < limit; no++)
    {
     if (no != global.ix)  {*chng = *orig; chng++; orig++;}
     else                  { orig++ ;} // skipping
    }

  free(text[fetch].row); 
  text[fetch].row = new; text[fetch].size = limit; 

  int testa = inAline(global.ix,global.iy);
  int testb = inWindow(global.ix,global.iy);

  if (!(testa && testb)) die("quitting in del_key");

  return;

}

