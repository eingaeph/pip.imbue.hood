# Project pip.imbue.hood 

  The following write is over a year old and does not describe the 
  current stage of the project. The recent work is contained in 
  directory libk, and is slightly documented in libk.pdf store in
  that directory. 

  Previously the project sought to
  build illustrative code snippets to highlight a subset of idioms
  used in kilo.c. Snippet codes should execute without warnings and
  should be of a size readable in hour. 

  Illustrate GNU/Linux library calls sufficient to 
  display and edit text files without dependencies beyond the choice 
  of terminal emulator (gnome-terminal tested). Construct explanatory 
  html pages stored in tutor.zip.

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

