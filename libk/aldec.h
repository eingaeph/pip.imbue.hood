int readAfile(char *filename);
int readAline(void);
void wind(int xmin, int xmax, int ymin, int ymax, int lastline);

int  ReadKey(void);
void die(const char *s);
int  encode (int count, char* seq);

void enableRawMode(void);
void disableRawMode(void);
int  getCursorPosition(int* rows, int* cols);
void screenTest(void);
void uvset(void);
