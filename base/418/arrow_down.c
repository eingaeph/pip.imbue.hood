

int arrow_down(void)
{

  int iy = global.iy; 
  int ix = global.ix;
  int ymax = global.ymax;
  int lastline = global.lastline;

  iy++; if(iy > lastline ) iy = lastline;

  int size = text[iy].size;
  if (size < ix + 1 )  ix = size - 1;
  if (size = 0) ix = 0;

//store the insertion point 

  global.ix   = ix;
  global.iy   = iy;

  return 0;

}

