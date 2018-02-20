
int inWindow(int ix, int iy) 
{
  
    int xmin = global.xmin;    /* window edges in text coordinates */
    int ymin = global.ymin;
    int xmax = global.xmax;
    int ymax = global.ymax;

    int testa = (ix >= xmin) && (ix <= xmax); 
    int testb = (iy >= ymin) && (iy <= ymax);
  
    return testa && testb;     /* returns true inside the window   */

}

