#include "../libk.h"

void init(int argc, char** argv)
{
    if(argc < 2) die("filename not entered as argument");

//  read input file, initialize text and numbLines

    char * filename = argv[1]; 
    glob.numbLines = readAfile(filename); 
    assert(glob.numbLines > 0);

//  query screen for size, write initial window using rows and cols
//  uvset returns values through standard input
    
    enableRawMode(); uvset(); disableRawMode();

//  write initial window using rows and cols, not using xmin etc.

    screenTest();

//  set initial insertion point, in text coordinates of course

    glob.ix = 0; glob.iy = 0;

//  set xmin, xmax, ymin, ymax

    glob.xmin = 0; glob.xmax = glob.cols -1;
    glob.ymin = 0; glob.ymin = glob.rows -1;  
    if(glob.rows > glob.numbLines) glob.ymax = glob.numbLines -1; 

    return;
}



