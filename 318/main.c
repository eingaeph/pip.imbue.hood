

int main(int argc, char** argv)
{

  init(argc, argv);

  while (1) 

   {

    int tests = 1; int retval;

    if (tests) retval = replay();
    else       retval = ReadKey(); write(global.fpscp,&retval,sizeof(retval));

    wts("testing \n\r");

    int test = (retval != CTRL_U);

    if (test)
      {
        edal(retval, global.iy);

        setWindow();

        window(global.xmin,global.xmax,
               global.ymin,global.ymax);
      }

    else sear();
  
   }

  return 0; // this statement is never reached
}
