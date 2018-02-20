

int main(int argc, char** argv)
{

  init(argc, argv);

  while (1) 

   {
    int retval = ReadKey();

    edal(retval, global.iy);

   writeToScreen("x:global.ix = ");writeDigit(global.ix,1); writeToScreen("\n\r");
   writeToScreen("x:global.iy = ");writeDigit(global.iy,1); writeToScreen("\n\r");

    setWindow();

   writeToScreen("x:global.xmin = ");writeDigit(global.xmin,1); writeToScreen("\n\r");
   writeToScreen("x:global.ymin = ");writeDigit(global.ymin,1); writeToScreen("\n\r");

   writeToScreen("x:global.xmax = ");writeDigit(global.xmax,1); writeToScreen("\n\r");
   writeToScreen("x:global.ymax = ");writeDigit(global.ymax,1); writeToScreen("\n\r");

    window(global.xmin,global.xmax,
           global.ymin,global.ymax);
   }

  return 0; // this statement is never reached
}
