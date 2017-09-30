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

    char *ptr;

int main(void) {

    ptr = "this is my story";

    line.row = ptr;
    line.size = strlen(ptr);

    text = malloc(10*sizeof(slot));
    
    text[0] = line;
    printf("text[0].row = %s\n",text[0].row);

    ptr = "this is my song";
    line.row = ptr;
    line.size = strlen(ptr);

    text[1] = line;
    printf("text[1].row = %s\n",text[1].row);
    printf("text[0].row = %s\n",text[0].row);
 
    ptr = "tell me your song";
    line.row = ptr;
    line.size = strlen(ptr);

    text[3] = line;
    printf("text[3].row = %s\n",text[3].row);

    return 0;
}

