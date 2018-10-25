
// replay.c Duplicates a keystroke stream 
// for testing purposes 

int replay(void)
{
 int iw = 2234567; waiter(iw); // iw = 1234567;

 int store[200]; char c; int retval;

 int j = 1;
            store[j] = PAGE_DOWN;  j++;

            store[j] = ARROW_DOWN; j++;
            store[j] = ARROW_DOWN; j++;
            store[j] = ARROW_DOWN; j++;
            store[j] = END_KEY;    j++;
            store[j] = ARROW_UP;   j++;
            store[j] = ARROW_UP;   j++;
            store[j] = PAGE_DOWN;  j++;
            store[j] = ARROW_UP;   j++;
            store[j] = ARROW_UP;   j++;
            store[j] = END_KEY;    j++;
            store[j] = ENTER;      j++;
            store[j] = PAGE_UP;    j++;
            store[j] = PAGE_UP;    j++;
            store[j] = PAGE_UP;    j++;

            store[j] = CTRL_Q;     j++;

 global.noscript++;
 if (global.noscript < j) retval = store[global.noscript];
 else die("ending in function replay");

 return retval;

}
