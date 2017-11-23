#! /usr/bin/tcc -run

#include <stdio.h>
#include <stdlib.h>

void wrap(char **ps, char ***pps, int y, int x)
{

    *ps = x + *(*pps + y); 

}

int main(int arc, char** argv)
{
    int MAX = 4;
    char** row = malloc(MAX*sizeof(char*));
    row[0] = "this is my story";
    row[1] = "this is my song";
    row[2] = "i sing my story";
    row[3] = "all day long";

    MAX = MAX + 1;
    row = (char **) realloc(row,MAX*sizeof(char*));
    row[MAX - 1] = "Play it again, Sam";

    MAX = MAX + 1;
    row = (char **) realloc(row,MAX*sizeof(char*));
    row[MAX - 1] = "Do it for me";

    MAX = MAX + 1;
    row = (char **) realloc(row,MAX*sizeof(char*));
    row[MAX - 1] = "0123456789";

    char *ps;
    char **pps;
   
    pps = row;
    ps = *pps;

    int y = 0;
    int x = 0;
    wrap(&ps,&pps,y,x);
    printf("%s\n",ps);

    y = 1;
    x = 0;
    wrap(&ps,&pps,y,x);
    printf("%s\n",ps);

    y = 6;
    x = 0;
    wrap(&ps,&pps,y,x);
    printf("%s\n",ps);

    y = 6;
    x = 5;
    wrap(&ps,&pps,y,x);
    printf("%s\n",ps);

   
    return 0;
 }


