# Project pip.imbue.hood 

  As necessary build illustrative code snippets to support 
  minimal readability mods to kilo.c. Illustrate library function 
  calls sufficient to display and edit text files without further 
  dependencies in a Linux environment. Construct explanatory html
  pages stored in tutor.zip.

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
  who works with Sanfilippo's code. Ruten works at a deeper level and 
  renders this work a partial redundancy. But possibly his work is 
  not directly usable for the this project. The project's
  goal is "achieving a primary school understanding of kilo.c"
  whereas Ruten, at the least, works at the high school level.
  
  Code modifications to kilo in UPD format to reduce the temptation to 
  rewrite.

  Tutorial Tasks Outline:

  A. Describe a Linux terminal as a Linux device consuming character
     strings and emitting keystroke (characters) and display state 
     status strings.

  B. Document the coding style used by kilo: example screen reads 
     and writes.

  Lessons: Build around stand alone (scaffolding) code, chosen to be 
           readable in one sitting,so as to encourage the student to
           proceed reading kilo.c without mastering all the details. 
           To this end, insofar as possible. code in kilo.c style

  A. "KEY PRESSES"
     KEYP: Set terminal in raw mode, read keypresses, write 
     annotations to the display. Use kilo.c enum style to deal
     with keyboard emitted escape sequences

  B. "DISPLAY"
     DISP: Starting with a simple hard coded string based on VT100 
     escape sequences, copy the string to the display, clear the 
     screen, write a message, position the cursor.

  C. "BUILD E STRUCT"
     BEST: Build struct E in kilo.c style, that is a struct containing
     an array of structs, each element array elemtnt describing a line
     ultimately . 

  D. "SCROLL THE DISPLAY": SCROL
     Scroll the display with coding in kilo.c E struct style

  E. "FILE TO E": FELT 
     read a text file, store in an E struct
     
  Modifications to Kilo (UPD format)
  
  B. Trace representative source executable statements as tasks are
     carried out

  C. Add coding to count the calls to abAppend

  D. Add coding to file save the character string for later examination.

  E. Add coding to write the first screen incrementally, ie after each
     call to to abAppend. Insert a variable delay to allow a human to 
     see and follow what is going on. 

