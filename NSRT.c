#! /usr/bin/tcc -run

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

 char *orig = "this is my story how long is your day";
 char *chng ; 

void insert(int i, char c)
{
 char *worka = orig;
 char *workb = chng;

 printf("insert %c at position %d\n", c, i);

 int no; int limit=strlen(orig) + 1;
 for (no = 0 ; no < limit + 1; no++)
 {if (no != i) 
       {*workb = *worka; worka++; workb++;}
  else {*workb = c; workb++;}
 }
}

void delete(int i)
{
 char *worka = orig;
 char *workb = chng;

 printf("delete character at position %d\n", i);

 int no; int limit=strlen(orig) + 1;
 for (no = 0 ; no < limit + 1; no++)
 {if 
     (no != i) {*workb = *worka; worka++; workb++;}
  else         {worka++;}
 }
}


int main(void) {

 chng = malloc(100*sizeof(char));

 insert(11,'Q'); // insert a character

 printf("%s\n",orig); printf("%s\n",chng);

 delete(11); // delete a character

 printf("%s\n",orig); printf("%s\n",chng);

 return 0;
}
