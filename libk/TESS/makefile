stem    = /home/ubuntu/git/repo.1/libk/
new = TESS
old = REPL
nstem = $(stem)$(new)/
ostem = $(stem)$(old)/
libn =  $(nstem)lib$(new).a
libo =  $(ostem)lib$(old).a

firs:
	echo $(new)      > /dev/null
	echo $(old)      > /dev/null
	echo $(nstem)    > /dev/null
	echo $(ostem)    > /dev/null
	echo $(libn)     > /dev/null
	echo $(libo)     > /dev/null
	echo $(testnumb) > /dev/null

cleano:
	rm -f *.o *.a 

dryrun:
	rm -f *.o *.a test.c
	gcc -Wall -c $(nstem)*.c

tester:
	rm -f *.o *.a $(libn) test.c inpu.dat replay.c
	ar x          $(libo)
	ar rcs        $(libn) *.o
	rm -f *.o
	#retrieve replay.$(testnumb) to serve as replay.c during this test
	cp replay.$(testnumb) replay.c 
	cp arrow_left.chg     arrow_left.c
	cp arrow_right.chg   arrow_right.c
	gcc -Wall -c $(nstem)*.c
	ar rs         $(libn) *.o
	# ar t        $(libn)
	rm -f *.o *.c test
	#retreive main.$(testnumb) to serve as main during this test
	cp main.$(testnumb) test.c
	gcc -Wall test.c $(libn) -o test
	rm -f test.c $(libn)
	cp inpu.$(testnumb) inpu.dat
	./test inpu.dat 

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


