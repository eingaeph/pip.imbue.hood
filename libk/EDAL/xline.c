// xline.c allocatge the space for a new line
// build aray of slots new with space for extra line
// free text[iy].row

#include "../libk.h"

void xline(int iy, char *firs, int lena, char *seco, int lenb)
{
  assert (iy >= 0); assert (iy <= glob.numbLines);
  if  (text[iy].row != NULL) 
       assert(text[iy].size > 0);
  else assert(text[iy].size == 0); 
  assert (lena >= 0); assert (lenb >= 0);

  slot *temp   = malloc((glob.numbLines+2)*sizeof(slot *));
  assert(temp != NULL);

// initialize the slots pointed to by array of pointers temp
// intitialize two new slots when j = iy
                     
  int j; int k = 0;

  for (j = 0; j <= glob.numbLines; j++) 
    {
     if (j != iy) { temp[k] = text[j];   k++; }
     else         { 
                    temp[k].row = firs; temp[k].size = lena; k++;
                    temp[k].row = seco; temp[k].size = lenb; k++; 
                  }
    }

  if(text[iy].row != NULL) free(text[iy].row); 

  slot *bigger = realloc(text,(glob.numbLines+2)*sizeof(slot));
  assert(bigger != NULL); text = bigger;

  for (j = 0; j <= glob.numbLines; j++) text[j] = temp[j];

  free(temp); glob.numbLines ++; glob.ix = 0; glob.iy++;

}
