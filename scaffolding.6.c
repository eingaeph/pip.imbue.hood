
#include <string.h>
#include <unistd.h>
#include <termios.h>

/* ======================= Low level terminal handling ====================== */

static struct termios orig_termios; /* Save original struct termios */

int
main()
    {

     tcgetattr(STDOUT_FILENO, &orig_termios);
     tcsetattr(STDOUT_FILENO, TCSANOW, &orig_termios);

return 0;
}
