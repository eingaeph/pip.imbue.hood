#! /usr/bin/tcc -run

#include <unistd.h>   //read,write
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h> //open,close per Kerrisk page 72
#include <fcntl.h>    //open,close 

    size_t linecap;
    int nread;
    struct { int fp; int nread; } nput;

typedef struct slot
{
    ssize_t size;
    char *row;
    int count;
}   slot;

    slot line;
    slot *text;

int getr(char **qtr) // getline replacement
{
  char line[240];     // sets maximum linesize at three times reasonable
  char* s = &line[0]; // s and line are nearly each other's  alias
  int linesize;
  char* ptr;

  linesize = 0; s = &line[0];
  while((nread = read(nput.fp,s,1))==1) {if (*s != '\n') {s++; linesize++;} else break;}
   
/***
  here nread = EOF 0,ERROR 1 
       linesize is posibly zero, possibly greater than zero
***/

  if (linesize != 0) {ptr = malloc(linesize*sizeof(char));}
  if (linesize != 0) memcpy(ptr,line,linesize);
  if (linesize != 0) *qtr = ptr;
  return linesize;
}

int addAline(int here,int maxndx)

{
    int newlen = maxndx + 1 + 1;
    slot *new  = (slot *)malloc(newlen*sizeof(slot));

    slot newline;
    char *ptr = "Yes, I am a new line!\n";
    newline.size = strlen(ptr)-1;
    char *qtr = (char *)malloc(strlen(ptr)-1);
    memcpy(qtr,ptr,strlen(ptr)); 
    newline.row = qtr;

    slot *old = text; 

    int i,j,k; i = 0; j = 0; k = 0;
    for (i = 0 ; i < maxndx + 1 ; i++) 
      {if (i != here) {new[j] = old[k]; j++; k++;}
       else           {new[j] = old[k]; j++; k++;
                       new[j] = newline;     j++;}
      }


    free(text); text = new;  
   
    maxndx++;
    return maxndx;
}

int deleteAline(int omit,int maxndx)
{
    int newlen = maxndx + 1 - 1;
    slot *new  = (slot *)malloc(newlen*sizeof(slot));

    slot *old = text; 

    int i,j,k; i = 0; j = 0; k = 0;
    for (i = 0 ; i < maxndx + 1 ; i++) 
      {if (i != omit) {new[j] = old[k]; j++; k++;}
       else           {                      k++;}
      }

    free(text[omit].row);
    free(text); text = new;  

    maxndx--;
    return maxndx;
}

void etxt(int maxndx)
{
    write(1,"\n",1);

    int i;
    for (i = 0; i < maxndx + 1; i++)
      {
       write(1,"text[",5);
       char buf[7];
       snprintf(buf,3,"%2d",i);
       write(1,buf,2);
       write(1,"].row: ",7);
       write(1,text[i].row,text[i].size); 
       write(1,"\n\r",2);
      } 
    return;
}

// function replaceAline 
// makes one call to malloc for replacement text  
// plus  one call to free text[nsrt].row (the replaced element)
// plus  one call to free text (the entire replaced document)

int replaceAline(int nsrt,int maxndx)
{
    int newlen = maxndx + 1 + 0;
    slot *new  = (slot *)malloc(newlen*sizeof(slot));

    slot newline;
    char *ptr = "Hello World! I am a replacement line.\n";
    newline.size = strlen(ptr)-1;
    char *qtr = (char *)malloc(strlen(ptr)-1);
    memcpy(qtr,ptr,strlen(ptr)); 
    newline.row = qtr;

    slot *old = text; 

    int i,j,k; i = 0; j = 0; k = 0;
    for (i = 0 ; i < maxndx + 1 ; i++) 
      {if (i != nsrt) {new[j] = old[k]; j++; k++;}
       else           {new[j] = newline;j++; k++;}
      }

    free(text[nsrt].row);
    free(text); text = new;  

    return maxndx;
}

int readAline(void)
{
    line.row = 0; linecap = 0;
//  line.size = getline (&line.row, &linecap,nput.fp); 
    line.size = getr(&line.row);    

    if (line.size == -1) {return line.size;}

    if((line.count == 0)) 
         { text = (slot *) malloc(     (1+line.count)*sizeof(slot));}
    else { text = (slot *)realloc(text,(1+line.count)*sizeof(slot));}

    char * ptr = malloc(line.size*sizeof(char));
    text[line.count].row = ptr  ;
    text[line.count].size = line.size;
    memcpy(ptr,line.row,line.size);  

    line.count++; 
    return 0;
}

int main(int argc, char** argv)
{
    char* filename = argv[1];
    int numb; int retval; int lastline;

    if(argc == 1) return 0;

    write(1,argv[1],strlen(argv[1]));
    write(1,"\r\n",2);

    nput.fp = open(filename,O_RDONLY);

    line.count = 0;
    for (numb = 0 ; numb < 100; numb++) 
    {
    retval=readAline(); 
    if (nread == 0) {break;}
    lastline = line.count; 
    }

    char buf[8];
    snprintf(buf,8,"%d\n",lastline);
    write(1,buf,strlen(buf));
    write(1," lines were read\n\r",17);

    int maxndx = lastline - 1; etxt(maxndx);

    maxndx = replaceAline(5,maxndx); etxt(maxndx);

    maxndx = deleteAline(7,maxndx); etxt(maxndx);

    maxndx = addAline(2,maxndx); etxt(maxndx);
    close(nput.fp);
    return 0;
 }

