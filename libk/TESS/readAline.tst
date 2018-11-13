#include "../libk.h"
/*
    malloc/realloc struct text
    text[line.count].row
    text[line.size].size
*/
int readAline(void)
{
    line.row = NULL; linecap = 0;
    line.size = getline (&line.row, &linecap, fp); 
    printf("line.size = %lu\n\r",line.size);

    if (line.size == -1) {return line.size;}
    assert(line.size >= 1);

    line.size = line.size - 1;

    if((line.count == 0)) {text = malloc(sizeof(slot));}
    else {text = realloc(text,(1+line.count)*sizeof(slot));}

    char * ptr = malloc(line.size*sizeof(char));
    text[line.count].row = ptr  ;
    text[line.count].size = line.size;
    memcpy(ptr,line.row,line.size);

//    printf("the string at text[].row:  %.*s", 
//    text[line.count].size, text[line.count].row);  

//    printf("line.count = %d text[iy].size =%lu  \n\r",line.count,text[line.count].size);

    line.count++; 
    return 0;
}


