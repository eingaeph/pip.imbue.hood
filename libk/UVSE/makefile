stem    = /home/ubuntu/git/repo.1/libk/
clib = UVSE
udir = $(stem)UVSE/

cleano:
	rm -f *.o *.a

linkall:
	rm -f *.o *.a $(udir)lib$(clib).a test$(clib)
	gcc -Wall -c  $(udir)*.c
	ar  rcs       $(udir)lib$(clib).a *.o
	ar  t         $(udir)lib$(clib).a
	rm -f *.o
	cp main.$(clib) test.c
	gcc -Wall test.c $(udir)lib$(clib).a -o test$(clib)
	rm -f test.c
	./test$(clib) 

count:
	cat $(udir)*.c | wc
