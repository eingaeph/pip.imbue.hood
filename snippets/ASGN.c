//#! /usr/bin/tcc -run

//replace assignments with memcpy

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct {ssize_t size; char *row; int count;} slot; slot line; slot *text;

int main(void)
{
  slot aline, bline, cline;

  aline.row = "sing that story";      //memory for string allocated here
  aline.size = strlen(aline.row);

  cline.row = "sorry charlie";        //memory for string allocated here
  cline.size = strlen(cline.row);

  bline = aline;
  printf("%s\n\r",bline.row);

  slot *test = malloc(5*sizeof(slot));
  test[1] = bline;
  test[0] = cline;
  printf("%s\n\r",test[1].row);
  printf("%s\n\r",test[0].row);
  exit(0);

// use memcpy instead of assignment operator = to iniitialize a slot
// void *memcpy(void *dest, const void *src, size_t n);

   memcpy(&bline,&aline,sizeof(slot)); 

// assert(aline == bline) fails to compile 
   assert(aline.row == bline.row); // succeeds during execution

// The malloc() function allocates size bytes and returns a pointer to the
// allocated memory. 

  slot *book = malloc(5*sizeof(slot)); //book = pointer to contiguous memory for 5 slots
                                       //book + 0 = pointer to first slot
                                       //book + 1 = pointer to second slot 

  assert( (book+2) == &book[2] );

// Whenever an expression such as X[k] appears in a program, 
// the compiler interprets it to mean *(X + k)

  memcpy(book+0, &aline, sizeof(slot));
  memcpy(book+1, &bline, sizeof(slot));
  memcpy(book+2, &cline, sizeof(slot));
  printf("%s\n",book[0].row);
  printf("%s\n",book[1].row);
  printf("%s\n",book[2].row);
  printf("\n");

  slot *tabl = malloc(5*sizeof(slot));
  assert( (tabl+2) == &tabl[2] );
  memcpy(tabl+2,book+2,sizeof(slot));
  printf("%s\n",tabl[2].row);
  printf("\n");

  memcpy(&tabl[1],&book[1],sizeof(slot));
  assert( tabl+1 == &tabl[1]);
  printf("%s\n",tabl[1].row);
  printf("%s\n",(tabl+1)->row);

  printf("stopping\n");
  return 0;
}
