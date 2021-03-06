# Project pip.imbue.hood 

  The writeup in the next section 
  is over a year old and does not describe the current 
  direction of the project. The recent work is contained in 
  directory libk, and is slightly documented in libk.pdf stored in
  that directory. The functionality of the library in libk/REPL is
  1) read an input text file, 
  2) function as a pager to display the  input file with horizontal 
and vertical scrolling 
  3) perform several text editing functions. 

# The Build

  The library build is accomplished by the bash script gath/scrip. The
  build performs test exercises on test executables, and requires user
  input to exit test editors and before proceeding to the next step. This 
  will probably irritate folks who are not an author, but we love the slight 
  gain in assurance that the build is going correctly. 

  Project pip/imbue/hood forked from the antirez writing at the data
  structure level. subKilo deals with text coordinates, x and y, and
  and window coordinates, u and v, while Kilo works with the offset 
  between those alternative coordinates.  We are irrationally attached
  to our choice of data structure, because, reasons.

# Code Snippets to Ilustrate C Idioms 

  Previously the project sought to
  build illustrative code snippets to highlight a subset of idioms
  used in kilo.c. Snippet codes should execute without warnings and
  should be of a size readable in hour. 

  Illustrate GNU/Linux library calls sufficient to 
  display and edit text files without dependencies beyond the choice 
  of terminal emulator (gnome-terminal tested) and the widely available
  gcc standard libraries. Construct explanatory html pages stored in 
  tutor.zip.

  The project wishes to support kilo.c as a preliminary archive of 
  working C idioms. The present work is explicitly not an attempt to 
  fork kilo.c but is intended to support a first reading of kilo.c, 
  while allowing skipping past many details. The idea arises from
  the realization that mastering all the details in xterm, etc., is
  very unwise and counterproductive. 

  Prototype code kilo.c by Salvatore Sanfilippo is hosted at
  http://github.com/antirez/kilo.

  Lausler's code https://github.com/pklausler/aoeui is an alternative
  prototype built to very similar specifications of length and
  dependencies and has been used been proven useful (by the author)
  for years. 

  The prototype code contains a copyright notice (2016). It is 
  licensed by Salvatore Sanfilippo under terms which are here 
  incorporated as LICENSE.md. 

  Vigliag https://github.com/vigliag/kilo has forked Sanfilippo's code 
  adding comments explaining coding decisions etc.

  http://viewsourcecode.org links to a valuable tutorial by Jeremy.Ruten
  who works with Sanfilippo's code. Ruten works at an informative level and 
  renders this work a partial redundancy. But possibly his work is 
  not directly usable for the this project. This project's
  goal is "achieving a teachable primary school understanding of kilo.c"
  whereas Ruten, at the least, works at the high school level.
  
  Code modifications to kilo.c in UPD format to reduce the temptation to 
  rewrite.

  Scaffold Code Snippets (SCAFFOLD.md)

  Modifications to kilo.c (UPD format) to support executing tracing.
  
  A. Trace representative source executable statements as tasks are
     carried out.

  B. Add coding to file save the character string for later examination. 

  As a final step, add function and variable prototypes to support creation of
  separate compilation units and an ar archive to support stepwise recompilation
  by gcc.

