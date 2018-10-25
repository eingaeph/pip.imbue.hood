stem    = /home/ubuntu/git/repo.1/libk/
wdir = $(stem)WARF/
kdir = $(stem)KEYP/
udir = $(stem)UVSE/
edir = $(stem)EDAL/

cleano:
	rm -f *.o *.a

dryrun:
	rm -f *.o *.a test.c
	gcc -Wall -c $(edir)*.c

linkall:
	rm -f *.o *.a test.c
	gcc -Wall -c $(edir)*.c
	ar x         $(wdir)libWARF.a
	ar x         $(kdir)libKEYP.a
	ar x         $(udir)libUVSE.a
	ar rcs       $(edir)libEDAL.a *.o
	ar t         $(edir)libEDAL.a
	rm -f *.o test
	cp main.cold test.c
	gcc -Wall test.c $(edir)libEDAL.a -o test
	rm -f test.c
	./test test.dat

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

count:
	cat $(kdir)*.c $(udir)*.c $(wdir)*.c | wc
