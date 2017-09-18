
SCAFFOLD 

  Executable code snippets to point out and make readable Kilo.c 
  idioms. 

  Snippet IDs:

   BASC  --  Build a screen (alias DISP display)
   DCOD  --  Decode (parse) keyboard input stream
   REAF  --  Read a file
   WIND  --  Scrolled (windowed) view of text buffer


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