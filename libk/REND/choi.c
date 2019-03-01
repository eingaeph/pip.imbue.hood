#include "../libk.h"
/*
    choic.c

    call example:   if( choi(3,"bras") ) .....
*/
int choi(int flag, char option[5])
{
   printf("%s has length = %d\n",option,(int) strlen(option));
   assert(strlen(option)==4);
   char poss[] = "find" "bras";
   static int ibras; static int ifind;
   assert(strstr(poss, option)!=NULL);

   if(flag == 1) {if(!strcmp(option,"bras")) return ibras++ ;}
   if(flag == 2) {if(!strcmp(option,"bras")) return ibras=0 ;}
   if(flag == 3) {if(!strcmp(option,"bras")) return ibras   ;}

   if(flag == 1) {if(!strcmp(option,"find")) return ifind++ ;}
   if(flag == 2) {if(!strcmp(option,"find")) return ifind=0 ;}
   if(flag == 3) {if(!strcmp(option,"find")) return ifind   ;}

   assert(0);

}



