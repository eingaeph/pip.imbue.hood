#include "../libk.h"

void waiter(int iw)
{ 
  clock_t ticks1, ticks2;

  ticks1=clock();
  ticks2=ticks1;
  while((ticks2-ticks1)<iw) // iw = 1234567
         ticks2=clock();

//  printf("The wait time is %ld ticks.\n",ticks2-ticks1);
//  printf("This value of CLOCKS_PER_SEC is %d.\n",CLOCKS_PER_SEC);

}
