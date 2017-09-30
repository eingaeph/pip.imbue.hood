#! /usr/bin/tcc -run

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct slot
{
    ssize_t size;
    char *row;
}   slot;

    slot line;
    slot *text;
    slot *old;
    slot *new;

    char *ptr;

int main(void) {

    text = malloc(10*sizeof(slot));
    old  = malloc(10*sizeof(slot));
    new  = malloc(10*sizeof(slot));
   
    ptr = "this is my story";
    line.row = ptr;
    line.size = strlen(ptr);
    text[0] = line;


    ptr = "this is my song";
    line.row = ptr;
    line.size = strlen(ptr);
    text[1] = line;
  
 
    ptr = "tell me your song";
    line.row = ptr;
    line.size = strlen(ptr);
    text[3] = line;

    printf("text[3].row = %s\n",text[3].row);
    
    int j;

    slot newline;
    ptr = "Hello world!";
    newline.row = ptr;
    newline.size = strlen(ptr);

    for (j = 0; j < 10; j++) 
      {if (j != 3) {old[j] = text[j];}
       else        {old[j] = newline;}
      }
    printf("\n");
    printf("old[3].row = %s\n",old[3].row);
    printf("old[1].row = %s\n",old[1].row);



    return 0;
}

