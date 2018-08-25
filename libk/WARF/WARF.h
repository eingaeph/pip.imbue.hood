#include "../allib.h"

typedef struct {ssize_t size; char *row; int count;}   slot;

    slot line;
    slot *text;

    size_t linecap;
    FILE *fp;

