//  enter.c 
//  process ENTER returned by readKey.c  
//  a new line is created leaving the EOL at ix
//  newline firs is has length ix stored as lena
//  newline seco has the remainder of the original line, stored as lenb  

#include "../libk.h"

void enter(void)
{

  possibleLine; possibleIxIy;
 
//  calculate length of new lines

  int lena = glob.ix;                   // number of chars in newline firs
  int lenb = text[glob.iy].size - lena; // number of chars in newline seco

//  pointers to new lines

  char *firs; char* seco;

//  case ix = 0, lena = 0


  if (text[glob.iy].size == 0)
     {
      assert(glob.ix == 0); assert(glob.rows == NULL);
      assert(lena == 0); assert(lenb == 0); firs = NULL; seco = NULL;
      xline(glob.iy, firs, lena, seco, lenb);
      return;
     }

   assert(text[glob.iy].size > 0);

/*** build firs and seco ***/

  if (lena > 0) firs = malloc(lena*sizeof(char)); //string firs
  else          firs = NULL;                      //zero length 
  if (lenb > 0) seco = malloc(lenb*sizeof(char)); //string seco
  else          seco = NULL;                      //zero length

  char *chng = firs; // populate firs length lena 
  char *orig = text[glob.iy].row; 
  int no; for (no = 0 ; no < lena; no++)
    {*chng = *orig; chng++; orig++;}

  chng = seco;       // populate seco length lenb
  for (no = lena; no < lena + lenb; no++)
    {*chng = *orig; chng++; orig++;}

//xline, realloc, reallocate text to include extra line

   xline(glob.iy, firs, lena, seco, lenb);

}
