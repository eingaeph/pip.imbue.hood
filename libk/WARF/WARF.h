#include "../allib.h"

typedef struct {ssize_t size; char *row; int count;}   slot;

    slot line;
    slot *text;

    size_t linecap;
    FILE *fp;

int readAfile(char *filename);
int readAline(void);
void wind(int xmin, int xmax, int ymin, int ymax, int lastline);
