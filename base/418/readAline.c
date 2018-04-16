int readAline(void)
{  

    line.row = NULL; 
    line.size = getl(&line.row);  
    if(global.nread <= 0) return -1;

    if((line.count == 0)) 
         { text =  malloc(     (1+line.count)*sizeof(slot));}
    else { text = realloc(text,(1+line.count)*sizeof(slot));}

    if (line.size == 0) { 
                         text[line.count].size = 0; 
                         text[line.count].row  = NULL;
                         line.count++;
                         assert(line.row == NULL);
                         return line.size;
                        }

    assert(line.row != NULL);

    text[line.count].row = line.row;
    text[line.count].size = line.size;

    line.count++; 
    return line.size;
}

