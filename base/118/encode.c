
/*** handle escape sequences. ***/

int encode (int count, char* seq)
{
//  write(1,"encode at work  ",16);
//  write(1,"count = ",8);
//  writeDigit(count,STDOUT_FILENO);
//  write(1,"  ",2);

  char buf[] = "   ";

  buf[0] = seq[0] ; // write(STDOUT_FILENO,buf,1); 
  buf[0] = seq[1] ; // write(STDOUT_FILENO,buf,1); 
  buf[0] = seq[2] ; // write(STDOUT_FILENO,buf,1); 
  write(1,"\n\r",2);

  int testa = ( (seq[0] == '[')); 
  int testb = ( (count < 4 ) );
  int testc = ( (seq[2] == '~') );

  if (count < 3 ) return ESC;  // this is unusual
   
  if (!testa)     return ESC;

//  write(STDOUT_FILENO,"seq[1] = ",9); write(STDOUT_FILENO,&seq[1]    ,1);
//  write(STDOUT_FILENO,"\n\r"     ,2);

  if (testb) {
     switch(seq[1]) {
        case 'A': return ARROW_UP;
        case 'B': return ARROW_DOWN;
        case 'C': return ARROW_RIGHT;
        case 'D': return ARROW_LEFT;
        case 'H': return HOME_KEY;
        case 'F': return END_KEY;                            }
              }

  if (testc) {
     switch(seq[1]) {
        case '2': return INSERT_KEY;
        case '3': return DEL_KEY;
        case '5': return PAGE_UP;
        case '6': return PAGE_DOWN;
                    }
             } // else return ESC;  
     
  return ESC; // this is unusual 
}


