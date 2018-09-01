#include "../libk.h"


int readAline(void)
{
    line.row = NULL; linecap = 0;
    line.size = getline (&line.row, &linecap, fp); 

    if (line.size == -1) {return line.size;}

    if((line.count == 0)) {text = malloc(sizeof(slot));}
    else {text = realloc(text,(1+line.count)*sizeof(slot));}

    char * ptr = malloc(line.size*sizeof(char));
    text[line.count].row = ptr  ;
    text[line.count].size = line.size;
    memcpy(ptr,line.row,line.size);

//    printf("the string at text[].row:  %.*s", 
//    text[line.count].size, text[line.count].row);  

    line.count++; 
    return 0;
}


