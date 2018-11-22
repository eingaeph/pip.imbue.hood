//#! /usr/bin/tcc -run

//replace assignments with memcpy

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct {ssize_t size; char *row; int count;} slot;

    slot line; slot *text;

int main(void)
{

  slot aline;
  aline.row = "sing that story";      //memory for string allocated here
  aline.size = strlen(aline.row);

  slot bline;

  slot cline;
  cline.row = "sorry charlie";        //memory for string allocated here
  cline.size = strlen(cline.row);

// use memcpy instead of assignment operator =
// void *memcpy(void *dest, const void *src, size_t n);

  memcpy(&bline,&aline,sizeof(slot)); 

  assert(aline.row == bline.row);

// The malloc() function allocates size bytes and returns a pointer to the
// allocated memory. 

// Whenever an expression such as X[k] 
// appears in a program, 
// the compiler interprets it to mean *(X + k)

  slot *book = malloc(5*sizeof(slot)); //book = pointer to contiguous memory for 5 slots
                                       //book + 0 = pointer to first slot
                                       //book + 1 = pointer to second slot 
 
  memcpy(book+0, &aline, sizeof(slot));
  memcpy(book+1, &bline, sizeof(slot));
  memcpy(book+2, &cline, sizeof(slot));
  printf("%s\n",book[0].row);
  printf("%s\n",book[1].row);
  printf("%s\n",book[2].row);
  printf("\n");

  slot *tabl = malloc(5*sizeof(slot));
  memcpy(tabl+2,book+2,sizeof(slot));
  printf("%s\n",tabl[2].row);
  printf("\n");

  assert( (book+2) == &book[2] );
  assert( (tabl+2) == &tabl[2] );

  memcpy(&tabl[2],&book[2],sizeof(slot));
  printf("almost\n\r");
  printf("%s\n",tabl[2].row);
  printf("\n");
  
  
  printf("stopping\n");
  return 0;
}
