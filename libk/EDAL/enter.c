#include "../libk.h"

void enter(void)
{
  int ix = glob.ix;              // text x insertion point
  int iy = glob.iy;              // text y insertion point
  int numbLines = glob.numbLines;  // number of rows in text
  int lena = ix + 1;               // number of chars in newline firs
  int lenb = text[iy].size - lena; // number of chars in newline seco
  char *firs; char * seco;

  int testy = iy; testy = testy; possibleLine;

  int testa = (text[iy].size == 0) ;
  if (testa) assert(ix == 0);
  if (testa) {lena = 0; lenb = 0; firs = NULL, seco = NULL;}
  if (testa) xline(iy, firs, lena, seco, lenb);
  if (testa) return;

  assert(text[iy].size > 0);

/*** build firs and seco ***/

  if (lena > 0) firs = malloc(lena*sizeof(char)); //string firs
  else          firs = NULL;                      //zero length 
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

  slot *new  = malloc((numbLines+2)*sizeof(slot));
                      
  int j; int k = 0;

  for (j = 0; j <= numbLines; j++)  //build an array of slots
    {
     if (j != iy) { new[k] = text[j];   k++; }
     else         { 
                    new[k].row = firs; new[k].size = lena; k++;
                    new[k].row = seco; new[k].size = lenb; k++; 
                  }
    }


  if(text[iy].row != NULL) free(text[iy].row); 

  glob.numbLines ++; numbLines = glob.numbLines; 
  glob.ix = 0; glob.iy++;

  text = realloc(text,(numbLines+2)*sizeof(slot));
  for (j = 0; j <= numbLines; j++) {text[j] = new[j];}

  if (new != NULL) free(new);

}
