// xline.c 
// receive two character things, firs, seco 
// allocate the space for a new array of slots <temp>
// initialize the new array of slots, inserting firs and seco
// realloc text to the larger size then re initialize text 
// free temp
// free text[iy].row

#include "../libk.h"

void xline(int iy, char *firs, int lena, char *seco, int lenb)
{
printf("entering xline the value of text is %p\n\r",text);
  assert (iy >= 0); assert (iy < glob.numbLines);
  if  (text[iy].row != NULL) 
       assert(text[iy].size > 0);
  else assert(text[iy].size == 0); 
  assert (lena >= 0); assert (lenb >= 0);

  slot *temp   = malloc((glob.numbLines+1)*sizeof(slot *));
  assert(temp != NULL);

// initialize the slots pointed to by array of pointers temp
// intitialize two new slots when j = iy
                     
  int j; int k = 0;
printf("before temp initialization the value of text is %p\n\r",text);
printf("and the value of temp is %p\n\r",temp);
  for (j = 0; j < glob.numbLines; j++) 
    {
     if (j != iy) { temp[k] = text[j];   k++; }
     else         { 
                    temp[k].row = firs; temp[k].size = lena; k++;
                    temp[k].row = seco; temp[k].size = lenb; k++; 
                  }
    }
printf("before attempting the free the value of text is %p\n\r",text);
  if(text!= NULL) free(text); 
exit(0);
printf("numbLines = %d\n\r",glob.numbLines);
  slot *bigger = realloc(text,(glob.numbLines+1)*sizeof(slot));
  assert(bigger != NULL); text = bigger;
  for (j = 0; j <= glob.numbLines; j++) text[j] = temp[j];

  free(temp); glob.numbLines ++; glob.ix = 0; glob.iy++; possibleIxIy;

}
