stem    = /data.base/product/libk/
wdir = $(stem)WARF/
kdir = $(stem)KEYP/

linkall:
	rm -f *.o *.a
	gcc -Wall -c $(wdir)readAfile.c
	gcc -Wall -c $(wdir)readAline.c
	gcc -Wall -c $(wdir)wind.c
	ar x         $(kdir)libKEYP.a
	ar rcs       $(wdir)libWARF.a *.o
	ar t         $(wdir)libWARF.a
	rm -f *.o
	cp main.cold test.c
	gcc -Wall test.c $(wdir)libWARF.a -o test
	rm test.c
	./test test.dat
