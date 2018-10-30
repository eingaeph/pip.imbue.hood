stem    = /home/ubuntu/git/repo.1/libk/
clib = KEYP
olib = UVSE
kdir = $(stem)KEYP/
udir = $(stem)UVSE/
clib = KEYP

cleano:
	rm -f *.o *.a

linkall:
	rm -f *.o *.a $(kdir)lib$(clib).a test.c 
	ar x          $(udir)lib$(olib).a
	ar rcs        $(kdir)lib$(clib).a *.o
	ar t          $(kdir)lib$(clib).a
	rm -f *.o
	gcc -Wall -c $(kdir)*.c
	ar rs        $(kdir)lib$(clib).a *.o
	ar t         $(kdir)lib$(clib).a
	rm -f *.o test
	cp main.cold test.c
	gcc -Wall test.c $(kdir)lib$(clib).a -o test
	rm -f test.c
	./test

count:
	cat $(kdir)*.c $(udir)*.c | wc
