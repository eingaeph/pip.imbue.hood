stem    = /home/ubuntu/git/repo.1/libk/
new = gath
old = EDAL
nstem = $(stem)$(new)/
ostem = $(stem)$(old)/
libn =  $(nstem)lib$(new).a
libo =  $(ostem)lib$(old).a

firs:
	echo $(new)     > /dev/null
	echo $(old)     > /dev/null
	echo $(nstem)   > /dev/null
	echo $(ostem)   > /dev/null
	echo $(libn)    > /dev/null
	echo $(libo)    > /dev/null

cleano:
	rm -f *.o *.a 

dryrun:
	gcc -Wall -c $(nstem)*.c
	rm -f *.o
linkall:
	rm -f *.o *.a $(libn) test.c
	ar x          $(libo)
	ar rcs        $(libn) *.o
	rm -f *.o
	gcc -Wall -c $(nstem)*.c
	ar rs         $(libn) *.o
	ar t          $(libn)
	rm -f *.o test
	cp main.cold test.c
	gcc -Wall test.c $(libn) -o test
	rm -f test.c
	./test test.dat

count:
	cat ../UVSE/*c >  counter
	cat ../KEYP/*c >> counter 
	cat ../WARF/*c >> counter
	cat ../EDAL/*c >> counter
	cat ../REPL/*c >> counter
	cat ../VT100.h >> counter
	cat ../keyvals.h >> counter
	cat ../libk.h  >> counter
	wc counter
	rm -f counter

compileall:
	rm -f *.o *.a
	gcc -Wall -c $(kdir)ReadKey.c
	gcc -Wall -c $(kdir)die.c
	gcc -Wall -c $(udir)disableRawMode.c
	gcc -Wall -c $(udir)enableRawMode.c
	gcc -Wall -c $(kdir)encode.c
	gcc -Wall -c $(udir)getCursorPosition.c
	gcc -Wall -c $(wdir)readAfile.c
	gcc -Wall -c $(wdir)readAline.c
	gcc -Wall -c $(udir)screenTest.c
	gcc -Wall -c $(udir)uvset.c
	gcc -Wall -c $(wdir)wind.c
	ar  rcs       $(wdir)libWARF.a *.o
	ar  t         $(wdir)libWARF.a
	rm -f *.o
	cp main.cold test.c
	gcc -Wall test.c $(wdir)libWARF.a -o test
	rm test.c
	./test test.dat

