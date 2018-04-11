
// store the insertion point after arrow_up

int arrow_up(void)
{

  int iy = global.iy; 
  int ix = global.ix;

  assert(iy >= 0); if (iy == 0 ) return;
  iy--; 

  int size = text[iy].size;
  assert (size >= 0); 
    if (size == 0)
      { 
       ix = 0;
       global.ix = ix;
       global.iy = iy;
       return;
      }
  
    if (size < ix + 1)  ix = size - 1;

//store the insertion point 

  global.ix   = ix;
  global.iy   = iy;
  int testy = iy; possibleLine;

  return 0;

}

