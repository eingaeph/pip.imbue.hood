int getl(char **qtr)     // getline work-alike
{ 
  char inLine[240];      // sets maximum linesize at three times reasonable
  int inLineSize = 0; 
  char c;                // c and inLine[] are stored in the stack   
  
  int n = 0;
  while((global.nread = read(global.fpinp,&c,1))==1) 
    {if (c != '\n') {
                     assert (n < 241);
                     inLineSize++; 
                     inLine[n] = c; 
                     n++;
                    } else break;
    }

  if(global.nread <=0) return -1;

  if (inLineSize == 0) {*qtr = NULL; return inLineSize;}

  assert(inLineSize > 0);

  char *ptr = malloc(inLineSize*sizeof(char));
  memcpy (ptr,inLine,inLineSize*sizeof(char));

  *qtr = ptr; return inLineSize; // set qtr and return inLineSize
}


