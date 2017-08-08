#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

// To store multiple lines, 
// let’s make E.row an array of erow structs. 
// It will be a dynamically-allocated array, 
// so we’ll make it a pointer to erow, 
// and initialize the pointer to NULL.

typedef struct erow {
  int size;
  char *chars;
} erow;

struct editorConfig {
  int cx, cy;
  int screenrows;
  int screencols;
  int numrows;
  erow *row;
  struct termios orig_termios;
};

struct editorConfig E;

void editorAppendRow(char *s, size_t len) {
  E.row = realloc(E.row, sizeof(erow) * (E.numrows + 1));
  int at = E.numrows;
  E.row[at].size = len;
  E.row[at].chars = malloc(len + 1);
  memcpy(E.row[at].chars, s, len);
  E.row[at].chars[len] = '\0';
  E.numrows++;
}

int main() {
  E.numrows=0;
  char *greet="Hello World!";
  size_t len=strlen(greet);
  editorAppendRow(greet,len);
  printf("%d\n",len);
  printf("%s\n",greet);
  printf("%s\n",E.row[0].chars);
  }
