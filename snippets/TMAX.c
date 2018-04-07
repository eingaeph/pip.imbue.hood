#! /usr/bin/tcc -run

#include <string.h>  // memcpy
#include <stdio.h>   // printf
#include <stdlib.h>  // malloc
#include <assert.h>  // assert

#define textbound   texndx = (int) (text + iy);          \
                    assert(textmin <= texndx);           \
                    assert(textmax >= texndx);           

typedef struct {ssize_t size; char *row; int count;} slot;

    slot line; 
    slot *text;

int main(void)
{
 int leng = 10; 
 text = malloc(leng*sizeof(slot)); 

 int textmax = (int) (text + leng - 1);
 int textmin = (int) (text + 0);

 line.row = NULL;
 line.size = 0;

 int iy; for(iy = 0; iy < leng+1; iy++)     //deliberate iy overrun
   {
     printf("%d  text = %p\n",iy,text+iy);
     int texndx; textbound; 
     text[iy] = line;
   } 

 printf("test run ending\n");
 return 0;
}
