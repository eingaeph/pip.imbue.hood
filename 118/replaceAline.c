int replaceAline(int nsrt,int maxndx)
{
    printf("the start value of <text> pointer is %p\n", (void *)text);

    int newlen = maxndx + 1 + 0;
    slot *new  = (slot *)malloc(newlen*sizeof(slot));

    slot newline;
    char *ptr = "Hello World! I am a replacement line.\n";
    newline.size = strlen(ptr);
    char *qtr = (char *)malloc(strlen(ptr));
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
    printf("the end   value of <text> pointer is %p\n", (void *)text);

    return maxndx;
}
