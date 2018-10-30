#include "../libk.h"

void init(int argc, char** argv)
{
    if(argc < 2) die("filename not entered as argument");

//  read input file, initialize text and numbLinesq

    char * filename = argv[1]; 
    glob.numbLines = readAfile(filename); 

//  query screen for size, write initial window using rows and cols
//  uvset returns values through standard input
    
    enableRawMode(); uvset(); disableRawMode();

//  write initial window using rows and cols, not xmin etc.
//  printf("rows = %d\n\r",glob.rows); exit(0); 

    screenTest();

//  set initial insertion point, in text coordinates of course

    glob.ix = 0; glob.iy = 0;
  
    return;
}



