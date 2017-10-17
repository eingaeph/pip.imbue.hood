#! /usr/bin/tcc -run

#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>

enum KEY_ACTION{

        ESC = 27,           /* Escape */
        ARROW_LEFT = 1000

};

#include "IOCTL.my"

int main(){
    printf("Hello World!\n");
    int rows; int cols;
    if (getWindowSize(STDIN_FILENO,STDOUT_FILENO,
                      &rows,&cols) == -1)
    {
        perror("Unable to query the screen for size (columns / rows)");
        exit(1);
    }
    printf("rows = %d\n",rows);
    printf("cols = %d\n",cols);
 
}

