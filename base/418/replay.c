
// replay.c Duplicates a keystroke stream 
// 

int replay(void)
{
//  clock_t ticks1, ticks2;

//  ticks1=clock();
//  ticks2=ticks1;
//  while((ticks2-ticks1)<1034567)
//         ticks2=clock();

 int iw = 934567; waiter(iw); // iw = 1234567;

 int store[200]; char c; int retval;

 int j = 1;

 c = 'a';   store[j] = c;          j++;
 c = 'b';   store[j] = c;          j++;
            store[j] = PAGE_DOWN;  j++;
/*
            store[j] = ARROW_DOWN; j++;
            store[j] = ENTER;      j++;
            store[j] = ENTER;      j++;
            store[j] = ENTER;      j++;
            store[j] = ARROW_UP;   j++;
            store[j] = DEL_KEY;    j++;
*/
 c = 'm';   store[j] = c;          j++;
         
            store[j] = CTRL_Q;     j++;

 global.noscript++;
 if (global.noscript < j) retval = store[global.noscript];
 else die("ending in function replay");

//  printf("The wait time is %ld ticks.\n",ticks2-ticks1);
//  printf("This value of CLOCKS_PER_SEC is %d.\n",CLOCKS_PER_SEC);

  return retval;

}
