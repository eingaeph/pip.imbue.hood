stem    = /home/ubuntu/git/repo.1/libk/
clib = WARF
olib = KEYP
wdir = $(stem)WARF/
kdir = $(stem)KEYP/
udir = $(stem)UVSE/

cleano:
	rm -f *.o *.a

linkall:
	rm -f *.o *.a $(wdir)lib$(clib).a test.c
	ar x          $(kdir)lib$(olib).a 	
	ar rcs        $(wdir)lib$(clib).a *.o
	gcc -Wall -c  $(wdir)*.c
	ar rs         $(wdir)lib$(clib).a *.o
	ar t          $(wdir)lib$(clib).a
	rm -f *.o test$(clib)
	cp main.$(clib) test.c
	gcc -Wall test.c $(wdir)lib$(clib).a -o test$(clib)
	rm -f test.c
	./test$(clib) test.dat

count:
	cat ../*.h $(kdir)*.c $(udir)*.c $(wdir)*.c | wc
