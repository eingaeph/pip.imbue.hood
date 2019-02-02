stem    = /home/ubuntu/git/repo.1/libk/
new = FIND
old = XLIN
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
	rm -f *.o 
	cp main.FIND test.c
	gcc -Wall -c $(nstem)*.c
	rm -f *.o test.c

linkall:
	rm -f *.o *.a $(libn) test.c
	ar x          $(libo)
	ar rcs        $(libn) *.o
	rm -f *.o
	gcc -Wall -c $(nstem)*.c
	ar rs         $(libn) *.o
	ar t          $(libn)
	rm -f *.o test.c
	cp main.$(new) test.c
	gcc -Wall test.c $(libn) -o test$(new)
	rm -f test.c
	./test$(new) test.dat

count:
	cat ../UVSE/*c >  counter
	cat ../KEYP/*c >> counter 
	cat ../WARF/*c >> counter
	cat ../EDAL/*c >> counter
	cat ../REPL/*c >> counter
	cat ../XLIN/*c >> counter
	cat ../FIND/*c >> counter
	cat ../VT100.h >> counter
	cat ../keyvals.h >> counter
	cat ../libk.h  >> counter
	wc counter
	rm -f counter


