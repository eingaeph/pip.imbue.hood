char ReadKey() 
{
  char c; int nread;
  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) 
  if (nread == -1 && errno != EAGAIN) die("read");

  if (c == 17) write(STDOUT_FILENO,"\r\n",2);
  if (c == 17) exit(0);

  char test = 27;
  if (c != test) return c; 

//  write(STDOUT_FILENO,"escape = ",9);
//  writeDigit(c);
//  write (STDOUT_FILENO,"\r\n",2);

  char seq[3]={' ',' ',' '}; int count = 1;
 
  if (read(STDIN_FILENO, &seq[0], 1) == 1) {count++;}
  if (read(STDIN_FILENO, &seq[1], 1) == 1) {count++;}
  if (read(STDIN_FILENO, &seq[2], 1) == 1) {count++;}

//  write (STDOUT_FILENO,"count = ",9);
//  writeDigit(count);
//  write (STDOUT_FILENO,"\r\n",2);

  if (count > 1) {int ignore = encode(count,seq);}

  return c;
}


