#include "../libk.h"

void init(int argc, char** argv)
{
//  if(argc < 2) die("filename not entered as argument");

//  read input file, initialize text and numbLines

    char * filename = argv[1]; 
    glob.numbLines = readAfile(filename); 
   int iy; 
   for(iy=0; iy < glob.numbLines; iy++) {printf("%d   %lu\n\r",iy,text[glob.iy].size);}
   printf("glob.numbLines = %d\n\r",glob.numbLines);
   exit(0);

    assert(glob.numbLines >= 0);

//  queryscreen for size, write initial window using rows and cols
//  uvset returns values through standard input
    
    enableRawMode(); uvset(); disableRawMode(); 

//  write initial window using rows and cols, not using xmin etc.

    if(glob.numbLines == 0) {screenTest(); exit(0);}
    assert(glob.numbLines > 0);
    
//  set initial insertion point, in text coordinates of course

    glob.ix = 1; glob.iy = 0;
    printf("size = %lu\n\r",text[glob.iy].size);
//    exit(0);
    int iw = 4234567; waiter(iw); // iw = 1234567;

//  set xmin, xmax, ymin, ymax

    glob.xmin = 0; glob.xmax = glob.cols -1;
    glob.ymin = 0; glob.ymin = glob.rows -1;  
    if(glob.rows > glob.numbLines) glob.ymax = glob.numbLines -1; 

    return;
}



