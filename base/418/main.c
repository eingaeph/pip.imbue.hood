

int main(int argc, char** argv)
{

  init(argc, argv);

  statusBar();

  setWindow();

  window(global.xmin,global.xmax,
         global.ymin,global.ymax);

  while (1) 

   {

    int testa = 1; int retval;


    if (testa)  retval = replay();
    if (!testa) retval = ReadKey(); 

    if (retval == CTRL_Q) die("\n\n\n\n\r") ;

    int testb = (retval != CTRL_U);

    if (testb)
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