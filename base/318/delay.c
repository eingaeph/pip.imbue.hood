void delay(void)
{
  clock_t ticks1, ticks2;

  ticks1=clock();
  ticks2=ticks1;
//  while((ticks2-ticks1) < 1234567)
  while((ticks2-ticks1) < 1034567)
         ticks2=clock();
}

