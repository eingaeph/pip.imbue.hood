/* We define a very simple "append buffer" structure, that is an heap
 * allocated string where we can append to. This is useful in order to
 * write all the escape sequences in a buffer and flush them to the standard
 * output in a single call, to avoid flickering effects. */


//  struct abuf {
//    char *b;
//    int len;  };
//
// #define ABUF_INIT {NULL,0}
//
//    example use:
//
//    abAppend(&ab,"\x1b[?25l",6); /* Hide cursor. */

void abAppend(struct abuf *ab, const char *s, int len) 
{
    char *new = realloc(ab->b,ab->len+len);

    if (new == NULL) return;
    memcpy(new+ab->len,s,len);
    ab->b = new;
    ab->len += len;
}

void abFree(struct abuf *ab) { free(ab->b); }

