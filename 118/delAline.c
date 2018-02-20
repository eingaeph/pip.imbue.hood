void delAline(void)
{
  int ix = global.ix;       //x text insertion point
  int iy = global.iy;       //y text insertion point
  int ymax = global.ymax;   // maximum y value under window 
  int lastline = global.lastline; // number of rows in text

  if (iy == (lastline - 1)) return; // delete attempt fails
 
// <new> aray of slots new with space for one less line

  slot *new  = malloc((lastline-1)*sizeof(slot));
                       
  int j; int k = 0;
  for (j = 0; j < lastline; j++)  //build array of slots new
    {
     if (j != iy) { new[k] = text[j];  k++; }
     else         { k = k ; }
    }

  global.lastline-- ; lastline = global.lastline; 
  free(text[iy].row);
  global.ix = 0;
  if (lastline < (ymax + 1)) global.ymax = lastline - 1;

  text = realloc(text,lastline*sizeof(slot));
  for (j = 0; j < lastline; j++) text[j] = new[j];

  free(new);
  return; 
 
}
