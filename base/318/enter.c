void enter(void)
{
  int ix = global.ix;              // text x insertion point
  int iy = global.iy;              // text y insertion point
  int lastline = global.lastline;  // number of rows in text
  int lena = ix + 1;               // number of chars in newline firs
  int lenb = text[iy].size - lena; // number of chars in newline seco

  wts("entering enter.c    \n\r");
  int testy = iy; possibleLine;

  int testa = (text[iy].size == 0) ;
  if (testa) assert(ix = 0);
  if (testa) die("trying to enter a zero length line\n\r");

  assert(text[iy].size > 0);

/*** build firs and seco ***/

  char *firs;
  if (lena > 0) firs = malloc(lena*sizeof(char)); //string firs
  else          firs = NULL;                      //zero length
  char *seco; 
  if (lenb > 0) seco = malloc(lenb*sizeof(char)); //string seco
  else          seco = NULL;                      //zero length

  char *chng = firs; // populate firs length lena 
  char *orig = text[iy].row; 
  int no; for (no = 0 ; no < lena; no++)
    {*chng = *orig; chng++; orig++;}

  chng = seco;       // populate seco length lenb
  for (no = lena; no < lena + lenb; no++)
    {*chng = *orig; chng++; orig++;}

//build aray of slots new with space for extra line

  slot *new  = malloc((lastline+2)*sizeof(slot));
                      
  int j; int k = 0;

  for (j = 0; j <= lastline; j++)  //build an array of slots
    {
     if (j != iy) { new[k] = text[j];   k++; }
     else         { 
                    new[k].row = firs; new[k].size = lena; k++;
                    new[k].row = seco; new[k].size = lenb; k++; 
                  }
    }


  if(text[iy].row != NULL); free(text[iy].row); 

  global.lastline ++; lastline = global.lastline; 
  global.ix = 0; global.iy++;

  wts("call realloc, expand text    \n\r");
  writeDigit(lastline,1); wts("    \n\r");

  text = realloc(text,(lastline+2)*sizeof(slot));
  for (j = 0; j <= lastline; j++) {text[j] = new[j];writeDigit(j,1);wts("\n\r");}

  if (new != NULL); free(new);

}
