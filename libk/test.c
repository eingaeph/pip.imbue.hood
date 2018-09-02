
// use *x as an easy to type alias for the global accesible variable arg.var

struct  { int var; int ignore; } arg;

int main(void) { int* x; x = &arg.ignore; *x = 13; (*x)++; return *x; }
