#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int ignore;
char ClearScreen[15]="\x1b[2J";
int
main()
    {

     size_t size = strlen(ClearScreen);

     int last = (int) size;
     printf("the last character is indexed by %d\n",last);

     printf("%s\n",ClearScreen);

     char* filestring ="new";

  /* unlink filestring, if link exists */

     ignore = unlink(filestring);

  /* Create filestring anew. Open filestring for writing.
     specify append, but this is unnecessary */

     int fd = open (filestring, O_WRONLY | O_CREAT | O_APPEND , 0666);

     write (fd, ClearScreen, last);

     close (fd);

return 0;
}
