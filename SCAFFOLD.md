
SCAFFOLD 

  Construct small executable code snippets (invoke tcc with a shebang). A snippet 
  of source length in the hundreds of statements compiles, executes and displays
  output effectively instantaneously. (A tenth of a second delay is not noticable.)
  Speedy testing and small codes greatly reduces the debugging cost.

  The purpose of all this is to point out and make readable important kilo.c idioms. 

  Scaffoldings consists Snippets and Derivatives of Snippets:
   Derivatives are more difficult to debug than Snippets to debug.

  Snippet IDs: (demonstrated idioms, idioms are singular, often used, manners of 
                speaking)

   ADAL  --  Replace a line in text (an array of slot structs)
   BASC  --  Build a screen (alias DISP display a screen)
   DCOD  --  Decode (parse) the keyboard input stream
   REAF  --  Read a file into a dynamically dimensioned text buffer 
   WIND  --  Scrolled (windowed) view of text buffer
   INSP  --  Insertion point, cursor position

  Derivative IDs: (invocations, 
                   which are combinations of idioms summoning many demons)

   107   --  Built from bases REAF, ADAL. 

  Titles: 

   kilo.c             An Open Source Editor
                       for the Linux OS
                   With No (Other) Dependencies

   idiom MOCU          Move the Cursor

   idiom INSP     Control the Insertion Point and Cursor Position
                                   Using
                               Arrow Keys, Etc.

   idiom WIND     Scroll (Window) The Display 
                             of
                       The Text Buffer

   idiom BASC     Write a String to the Screen
                      Clear the Screen
                     Position the Cursor
                    Display "Hello World!"

  Tutorial Tasks Outline:

  A. Describe a Linux terminal as a Linux device consuming character
     strings and emitting keystroke (characters) and display state 
     status strings.

  B. Document the coding style used by kilo: example screen reads 
     and writes.

  Lessons: Build around stand alone (scaffolding) code, chosen to be 
           readable in one sitting, so as to encourage the student to
           confindently continue reading kilo.c without mastering all 
           the details. To this end, insofar as possible. code in 
           kilo.c style

  A. "KEY PRESSES"
     KEYP: Set terminal in raw mode, read keypresses, write 
     annotations to the display. Use kilo.c enum style to deal
     with keyboard emitted escape sequences

  B. "DISPLAY"
     DISP: Starting with a hard coded strings comprising  VT100 
     escape sequences, copy the string to the display, clear the 
     screen, write a message, position the cursor.

  C. "BUILD E STRUCT"
     BEST: Build struct E in kilo.c style, that is a struct containing
     an array of structs, each element array elemtnt describing a line
     ultimately . 

  D. "SCROLL THE DISPLAY": SCROL
     Scroll the display with coding in kilo.c E struct style

  E. "FILE TO T": FELT 
     read a text file, store in an t (text) structure 
