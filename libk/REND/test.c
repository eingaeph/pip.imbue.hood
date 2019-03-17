// test.FIND

#include "../libk.h"

int main(int arc, char** argv)
{

//   set pointer to input filename

    char *filename =argv[1];

    printf("test.FIND executing\n");
    printf("filename = %s\n",filename);

//  following is the init segment, later move to init()

    glob.numbLines = readAfile(filename);

//   set rows, cols

    enableRawMode(); uvset(); disableRawMode();

//  set initial window parms and insertion point

    glob.xmin = 0; glob.xmax = glob.cols -1;
    glob.ymin = 0; glob.ymax = glob.rows -1; 
    if(glob.ymax > glob.numbLines -1) glob.ymax = glob.numbLines -1;
  
    glob.iy = 0; glob.ix = 0;
    printf("\n%d lines were read\n\n",glob.numbLines);

/* ******************************************************************** */

  setWindow(); headwind();
  wind(glob.xmin,glob.xmax, glob.ymin, glob.ymax, glob.numbLines);
  tailwind();

  static int iq; iq = 0;
  char query[80]; char* s = query;

  while(1)
   {

    int retval = ReadKey(); if (retval == CTRL_Q) return 0;

/**** FIND functionality ******/


    int testa = (retval == CTRL_S) && (!iq) && (s == query);           //begin query entry
    int testb = (retval == CTRL_S) && (iq)  && ((int)( s- query) > 0); //end query entry
    int testc = (retval != CTRL_S) && (iq);                            //build query

    char choice;
    if (testa) choice = 'a';
    if (testb) choice = 'b';
    if (testc) choice = 'c';

    switch(choice) 
      {  
         case 'a':
           {
             iq = !iq;
             printf(CursorToTopLeft "\x1b[999B" "Enter search string");  
             fflush(stdout);
             break;
           }
         case 'b':
           { 
             iq = !iq; s = query; int look;
             modb(query);
             setWindow(); headwind();
//             wind(glob.xmin,glob.xmax, glob.ymin, glob.ymax, glob.numbLines);
             int maxindex = maxidx();
             char* abuf = malloc(sizeof(char)*maxindex); assert(abuf != NULL);
             char* rbuf = malloc(sizeof(char)*maxindex); assert(rbuf != NULL);
             bildABUF(&abuf,&look);
             void bildHL_1(query, abuf, &look);
             bildRBUF(abuf,&rbuf);
             if(abuf != NULL) free(abuf);
             if(rbuf != NULL) free(rbuf);
             if(arg3 != NULL) free(arg3);
             printf("%s",rbuf);
             tailwind();
             free abuf; free rbuf; 
             break;
           }
         case 'c':
           {
             char c = retval; // retrieve a 1 byte character from a 4 byte integer
             *s = c; s++;
             *s = '\0';
             printf(CursorToTopLeft "\x1b[999B" "query = %s",query);  fflush(stdout);
             break;
           }
     }
    
    if(testa || testb || testc) continue;

/**** EDAL functionality ******/

    editAline(retval,glob.iy);
    setWindow(); headwind();
    wind(glob.xmin,glob.xmax, glob.ymin, glob.ymax, glob.numbLines);
    tailwind();

   } //end while(1)
   
    assert(0); 
}
