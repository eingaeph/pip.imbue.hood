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

    if (line.size == -1) {return line.size;} /* read failure */

    line.size = line.size - 1;
    assert(line.size >= 0); 

    if((line.count == 0)) {text = malloc(sizeof(slot));}
    else {
           text = realloc(text,(1+line.count)*sizeof(slot));
           if(!text) assert(text);
         }

    char* ptr = NULL;
    if (line.size > 0) ptr = malloc(line.size*sizeof(char));
    text[line.count].row = ptr  ;
    text[line.count].size = line.size;

    if (line.size > 0) memcpy(ptr,line.row,line.size);

    line.count++; return 0;
}


