stem    = /data.base/product/libk/
kdir = $(stem)KEYP/
udir = $(stem)UVSE/
clib = KEYP

cleano:
	rm -f *.o *.a

linkall:
	rm -f *.o *.a test.c
	gcc -Wall -c $(kdir)*.c
	ar x         $(udir)libUVSE.a
	ar rcs       $(kdir)lib$(clib).a *.o
	ar t         $(kdir)lib$(clib).a
	rm -f *.o
	cp main.cold test.c
	gcc -Wall test.c $(kdir)lib$(clib).a -o test
	rm -f test.c
	./test test.dat

count:
	cat $(kdir)*.c $(udir)*.c | wc
