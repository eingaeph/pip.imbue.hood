stem    = /home/ubuntu/git/repo.1/libk/
wdir = $(stem)WARF/
kdir = $(stem)KEYP/
udir = $(stem)UVSE/
clib = WARF

cleano:
	rm -f *.o *.a

linkall:
	rm -f *.o *.a test.c
	gcc -Wall -c $(wdir)*.c
	ar x         $(kdir)libKEYP.a
	ar x         $(udir)libUVSE.a
	ar rcs       $(wdir)lib$(clib).a *.o
	ar t         $(wdir)lib$(clib).a
	rm -f *.o test
	cp main.cold test.c
	gcc -Wall test.c $(wdir)lib$(clib).a -o test
	rm -f test.c
	./test test.dat

count:
	cat ../*.h $(kdir)*.c $(udir)*.c $(wdir)*.c | wc
