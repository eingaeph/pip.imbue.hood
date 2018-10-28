// replay.c test a 
#include "../libk.h"

// replay.c returns retval identical readKey.c 
// after a keystroke stream 
// for testing purposes 

// prata page 515, nocalls has file scope, internal linkage
// nocalls is defined outside of all functions, with keyword static 
// nocalls is private its (current) translation unit
// by standard all static file scope variables initialize to zero so presumably
// the initialization of nocalls is not needed 

static int nocalls = 0;

int replay(void)
{

// call waiter for a pause before returning 

 int iw = 2234567; waiter(iw); // iw = 1234567;

 int store[200]; int retval;

// local variable store contains command test sequence

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

 nocalls ++;

 if (nocalls < j) retval = store[nocalls];
 else die("quitting after logic error in replay.c");

 return retval;

}
