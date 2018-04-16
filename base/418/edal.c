
// edit a line defined by the insertion point ix,iy
// edit operation is specified by int retval
// int retval is taken sequentially from the keyboard
//            or is supplied from replay.c

int edal(int retval, int fetch)
{ 
  char c = retval;         // retrieve a 1 byte character 
                           // from a 4 byte integer

  int ix   = global.ix;     // initial values of ix,iy
  int iy   = global.iy; 

  assert(iy == fetch);


  int test = (retval > 31 && retval < 127); // true for printable character

  if (test)                             {chin(c,fetch); return 0;}     
  if (retval == BACKSPACE)              {backspace();   return 0;}
  if (retval == ARROW_LEFT)             {arrow_left();  return 0;}
  if (retval == ARROW_RIGHT)            {arrow_right(); return 0;}
  if (retval == ARROW_UP   & iy != 0)   {arrow_up();    return 0;}
  if (retval == ARROW_DOWN )            {arrow_down();  return 0;}
  if (retval == ENTER)                  {enter();       return 0;}
  if (retval == CTRL_K)                 {delAline();    return 0;}
  if (retval == DEL_KEY)                {del_key(fetch);return 0;} 
  if (retval == HOME_KEY)               {global.ix = 0; return 0;} 
  if (retval == PAGE_DOWN)              {pageDown();    return 0;}
  if (retval == PAGE_UP)                {pageUp();      return 0;}
  if (retval == END_KEY)                {end_key();     return 0;}

  return 0;

}

/*
        ENTER  = 13,                
        ESC    = 27,        
        BACKSPACE =  127,   
        ARROW_LEFT = 1000,
        ARROW_RIGHT,
        ARROW_UP,
        ARROW_DOWN,
        DEL_KEY,
        HOME_KEY,
        END_KEY,
        PAGE_UP,
        PAGE_DOWN,
        INSERT_KEY,
*/
