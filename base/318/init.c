
void init(int argc, char** argv)
{
    int numb; int retval; int lastline;
    char *outt;

    if (argc == 1) return;

    enableRawMode();

    char * filename = argv[1];
    write(STDOUT_FILENO,filename,strlen(filename)); 
    write(STDOUT_FILENO,"\n\r",2);

    display = malloc(     (60)*sizeof(slot));

    global.fpinp = open(filename,O_RDONLY);
    global.fptra = open("/dev/pts/18", O_RDWR);
    global.fpscp = open("script",O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
//    global.fpscp = open("script",O_RDONLY);

   for (numb = 0 ; numb < 100; numb++) 
    {
     retval=readAline(); 
     if (global.nread == 0) {break;}
     lastline = numb; 
    }

    char mesa[]="lastline = ";

    write(STDOUT_FILENO,mesa,strlen(mesa));
    writeDigit(lastline,STDOUT_FILENO);
    write(STDOUT_FILENO,"\n\r",2);

    global.ix = 0; 
    global.iy = 0;    /* insertion point, text coordinates */

    global.xmin =  0;
    global.xmax = 79;
    global.ymin =  0;
    if (lastline < 24) global.ymax = lastline;
    else               global.ymax = 23; 

    global.cu = 0;    /*screen coordinates */
    global.cv = 0;
            
    global.umin = 0;
    global.umax = 80;
    global.vmin = 0;
    global.vmax = 24;

    global.lastline = lastline; 

    global.noscript = 0;

    buff.row  = malloc(1*sizeof(char));
    buff.size = 1;
  
}



