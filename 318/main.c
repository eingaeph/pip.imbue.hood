

int main(int argc, char** argv)
{

  init(argc, argv);

  while (1) 

   {
    int retval = ReadKey();

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
