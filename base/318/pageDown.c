

int pageDown(void)
{

// delta = ymax - ymin 

  int delta = 24;

// default action

   global.ymax = global.ymax + delta;
   global.ymin = global.ymin + delta;
   global.iy = global.ymin; global.ix = 0;

// edge cases 

   if(global.ymax > global.lastline) 
     {
      global.ymax = global.lastline;
      global.ymin = global.lastline - delta;
      global.ix = 0;
      global.iy = global.ymin;
     }
  
  if(global.ymin < 0) 
    {
     global.ymin = 0; 
     global.iy = 0;
     global.ix = 0;
    }

  possibleIxIy;
  possibleLine;

  wts("leaving pageDown.c \n\r");
  return 0;

}

