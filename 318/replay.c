int replay(void)
{
  clock_t ticks1, ticks2;

  ticks1=clock();
  ticks2=ticks1;
  while((ticks2-ticks1)<1934567)
         ticks2=clock();

 int retval;
 if (global.noscript < 9) 
     {
      global.noscript++;
      retval = ARROW_DOWN;
     }
 else 
     {
      global.noscript++;
      if (global.noscript < 21) retval = ARROW_RIGHT;
      else die("ending in replay");
     }

//  printf("The wait time is %ld ticks.\n",ticks2-ticks1);
//  printf("This value of CLOCKS_PER_SEC is %d.\n",CLOCKS_PER_SEC);

  return retval;

}
