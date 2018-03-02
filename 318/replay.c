int replay(void)
{
  clock_t ticks1, ticks2;

  ticks1=clock();
  ticks2=ticks1;
  while((ticks2-ticks1)<0634567)
         ticks2=clock();

 int store[200]; char c; int retval;

 int j = 1;

          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;          
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;          
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_RIGHT;j = j + 1;
          store[j] = ARROW_RIGHT;j = j + 1;
          store[j] = ARROW_RIGHT;j = j + 1;
          store[j] = ARROW_RIGHT;j = j + 1;
          store[j] = ARROW_UP;   j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
 c = 'a'; store[j] = c; j = j + 1;  
 c = 'b'; store[j] = c; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
 c = 'c'; store[j] = c; j = j + 1;
 c = 'd'; store[j] = c; j = j + 1;
          store[j] = ENTER;      j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_DOWN; j = j + 1;
          store[j] = ARROW_UP;   j = j + 1;
          store[j] = ARROW_UP;   j = j + 1;
          store[j] = ARROW_UP;   j = j + 1;
          store[j] = ARROW_UP;   j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;
          store[j] = DEL_KEY;    j = j + 1;


 global.noscript++;
 if (global.noscript < j) retval = store[global.noscript];
 else die("ending in function replay");

//  printf("The wait time is %ld ticks.\n",ticks2-ticks1);
//  printf("This value of CLOCKS_PER_SEC is %d.\n",CLOCKS_PER_SEC);

  return retval;

}
