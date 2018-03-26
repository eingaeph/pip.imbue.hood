

int main(int argc, char** argv)
{

  init(argc, argv);

  while (1) 

   {

    int testa = 1; int retval; testa = 0;

    if (testa) retval = replay();
    else       retval = ReadKey(); 


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
