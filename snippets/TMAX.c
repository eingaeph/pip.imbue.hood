#! /usr/bin/tcc -run

// demonstate testmin testmax consistency with malloc

#include <string.h>  // memcpy
#include <stdio.h>   // printf
#include <stdlib.h>  // malloc
#include <assert.h>  // assert

typedef struct {ssize_t size; char *row; int count;} slot;

    slot line; 
    slot *text;

int main(void)
{
 leng = 10; int numb;
 text = malloc(leng*sizeof(slot)); 

 int textmax = (int) (text + leng - 1);
 int textmin = (int) (text + 0);

 line.row = NULL;
 line.size = 0;

 int i; for(i = 0; i < leng+1; i++)     //deliberate overrun
   {
     printf("%d  text = %p\n",i,text+i);
     numb = (int) (text+i);
     printf("%d  numb = %x\n",i,numb);
     assert(textmin <= numb); assert(textmax >= numb);
     *(text+i) = line;
   } 

 printf("test run ending\n");
 return 0;
}
