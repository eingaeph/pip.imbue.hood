#include "../libk.h"

void init(int argc, char** argv)
{
    if(argc < 2) die("filename not entered as argument");

    char * filename = argv[1]; readAfile(filename);

//  query screen for size, write initial window using rows and cols
    
    uvset(); screenTest();

//  set initial insertion point, in text coordinates of course

    glob.ix = 0; glob.iy = 0;
    return;
}



