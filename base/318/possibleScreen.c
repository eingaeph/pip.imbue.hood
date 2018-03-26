void possibleScreen(void)
{
  int ymin = global.ymin;
  int ymax = global.ymax;
  int y;

  for (y = ymin; y <= ymax; y++)
    {
     assert(text[y].size >= 0 );
     assert(text[y].size < 200); 
     if(text[y].row == NULL) assert(text[y].size == 0);
     if(text[y].size == 0)   assert(text[y].row  == NULL);
    }
}
