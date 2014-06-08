CFLAGS := $(CFLAGS) -std=c99

test: testscanner testscanner.sh
	./testscanner.sh

testscanner: ../datescanner.c testscanner.c
	(cd .. ; make datescanner.c)
	cat ../datescanner.c testscanner.c > t.c
	${CC} -I.. -o $@ t.c
	rm t.c


clean:
	rm -f *.o
	rm -f testscanner
	rm -f y.tab.c
