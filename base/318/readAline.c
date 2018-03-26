int readAline(void)
{
    line.row = NULL; 
    line.size = getl(&line.row);  

    if (line.size == 0) { 
                         text[line.count].size = line.size; 
                         text[line.count].row  = NULL;
                         line.count++;
                         return line.size;
                        }

    if((line.count == 0)) 
         { text = (slot *) malloc(     (1+line.count)*sizeof(slot));}
    else { text = (slot *)realloc(text,(1+line.count)*sizeof(slot));}

    char * ptr = malloc(line.size*sizeof(char));
    text[line.count].row = ptr  ;
    text[line.count].size = line.size;
    memcpy(ptr,line.row,line.size);  

    line.count++; 
    return line.size;
}

