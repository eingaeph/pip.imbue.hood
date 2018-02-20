
int inAline(int ix, int iy)    /* test ix iy ok, in a line    */
{
  
    int lastline = global.lastline;  
    int size = text[iy].size;

    int testa = (iy <= lastline) && (iy >= 0); 
    int testb = (ix <= size )    && (ix >= 0);
  
    return testa && testb;     /* returns true in a line      */

}

