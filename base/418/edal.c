int edal(int retval, int fetch)
{ 
  char c = retval;         // retrieve a 1 byte character 
                           // from a 4 byte integer


  int ix   = global.ix;     // previous values of ix,iy
  int iy   = global.iy;
  int ymax = global.ymax;   // previous values of xmax,etc. 

  assert(iy == fetch);


  int test = (retval > 31 && retval < 127); // true for printable character

  if (test)                             {chin(c,fetch); return 0;}     
  if (retval == BACKSPACE  & ix != 0)   {global.ix-- ;  return 0;}
  if (retval == ARROW_LEFT & ix != 0)   {global.ix-- ;  return 0;}
  if (retval == ARROW_RIGHT)            {global.ix++ ;  return 0;}
  if (retval == ARROW_UP   & iy != 0)   {arrow_up();    return 0;}
  if (retval == ARROW_DOWN )            {arrow_down();  return 0;}
  if (retval == ENTER)                  {enter();       return 0;}
  if (retval == CTRL_K)                 {delAline();    return 0;}
  if (retval == DEL_KEY)                {del_key(fetch);return 0;} 
  if (retval == HOME_KEY)               {global.ix = 0; return 0;} 
  if (retval == PAGE_DOWN)              {pageDown();    return 0;}

  return 0;

}

