int getl(char **qtr)    // getline work-alike
{
  char inLine[240];     // sets maximum linesize at three times reasonable
  char* ptr;

  int inLineSize = 0; 
  char *s = &inLine[0];   //s and inLine are aliases of each other
  while((global.nread = read(global.fpinp,s,1))==1) 
    {if (*s != '\n') {s++; inLineSize++;} else break;}

  if (inLineSize == 0) {ptr = NULL; *qtr = ptr; return inLineSize;}

  ptr = malloc(inLineSize*sizeof(char));
  memcpy(ptr,inLine,inLineSize);
  *qtr = ptr;

  return inLineSize;
}


