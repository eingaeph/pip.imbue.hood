
//  enter.c process ENTER returned by readKey.c  
//  a new line is created leaving the EOL at ix
//  newline firs is has length ix stored as lena
//  newline seco has the remainder of the original line, stored as lenb  

#include "../libk.h"

void enter(void)
{

//  test for valid line in struct text

  int testy = iy; testy = testy; possibleLine;
 
//  retrieve insertion point variables from struct glob

  int ix = glob.ix;              // text x insertion point
  int iy = glob.iy;              // text y insertion point
  int numbLines = glob.numbLines;  // number of rows in text

//  calculate length of new lines

  int lena = ix;                   // number of chars in newline firs
  int lenb = text[iy].size - lena; // number of chars in newline seco

//  pointers to new lines

  char *firs; char* seco;

  int testy = iy; testy = testy; possibleLine;

//  case ix = 0, lena = 1 

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
