stem    = /home/ubuntu/git/repo.1/libk/
clib = KEYP
olib = UVSE
kdir = $(stem)KEYP/
udir = $(stem)UVSE/


cleano:
	rm -f *.o *.a

linkall:
	rm -f *.o *.a $(kdir)lib$(clib).a test$(clib)
	ar x          $(udir)lib$(olib).a
	ar rcs        $(kdir)lib$(clib).a *.o
	ar t          $(kdir)lib$(clib).a
	rm -f *.o
	gcc -Wall -c $(kdir)*.c
	ar rs        $(kdir)lib$(clib).a *.o
	ar t         $(kdir)lib$(clib).a
	rm -f *.o test$clib
	cp main.$(clib) test.c
	gcc -Wall test.c $(kdir)lib$(clib).a -o test$(clib)
	rm -f test.c
	./test$(clib)

count:
	cat $(kdir)*.c $(udir)*.c | wc
