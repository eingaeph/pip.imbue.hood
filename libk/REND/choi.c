#include "../libk.h"
/*
    choic.c

    call example:   if( choi(3,"bras") ) .....
*/
void choi(int flag, char option[5])
{

   char poss[] = "find bras";
   static int ibras; static int ifind 
   assert(strstr(poss, option)!=NULL);

   if(flag = 1) {if(option=="bras") return ibras++ ;}
   if(flag = 2) {if(option=="bras") return ibras=0 ;}
   if(flag = 3) {if(option=="bras") return ibras   ;}

   if(flag = 1) {if(option=="find") return ifind++ ;}
   if(flag = 2) {if(option=="find") return ifind=0 ;}
   if(flag = 3) {if(option=="find") return ifind   ;}

   assert(0);

}



