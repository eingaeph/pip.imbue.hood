#! /usr/bin/tcc -run

//demonstrate index out of bounds error 
//flagged by statement number

//set smax or tmax when malloc is called

#include <string.h>  // memcpy
#include <stdio.h>   // printf
#include <stdlib.h>  // malloc
#include <assert.h>  // assert

#define tbound   assert(t >= 0); assert(t <= tmax);
#define sbound   assert(s >= 0); assert(s <= smax);          

typedef struct {ssize_t size; char *row; int count;} slot;

    slot line; slot *text;
    int smax, tmax;

int main(void)
{
 int s,t,smax,tmax;
 int leng = 10; 
 text = malloc(leng*sizeof(slot)); tmax = leng - 1;

 line.row = NULL;
 line.size = 0;

// insert deliberate iy overrun in next line

 int iy; for(iy = 0; iy < leng +7; iy++)   
   {
     t = iy; tbound; text[iy] = line;
   } 

 line.row = "sing that story";
 line.size = strlen(line.row); smax = line.size -1;

// insert deliberate s overrun in next line

 for(s = 0; s < line.size + 5; s++)
   {
     sbound; printf("%c",line.row[s]);
   }
 printf("\n");

// put deliberate t out of bounds in next line

   t=-15; tbound; text[t] = line; 
   printf("%s\n",text[t].row);

 printf("test run ending\n");

 return 0;
}
