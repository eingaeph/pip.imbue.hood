stem    = /home/ubuntu/git/repo.1/libk/
clib = UVSE
udir = $(stem)UVSE/

cleano:
	rm -f *.o *.a

linkall:
	rm -f *.o *.a $(udir)lib$(clib).a test
	gcc -Wall -c  $(udir)*.c
	ar  rcs       $(udir)lib$(clib).a *.o
	ar  t         $(udir)lib$(clib).a
	rm -f *.o
	cp main.cold test.c
	gcc -Wall test.c $(udir)lib$(clib).a -o test
	rm -f test.c
	./test 

count:
	cat $(udir)*.c | wc
