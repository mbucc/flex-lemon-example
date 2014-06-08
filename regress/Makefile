CFLAGS := $(CFLAGS) -std=c99

test: testscanner testscanner.sh
	./testscanner.sh

testscanner: ../datescanner.c tokentos.c testscanner.c
	cat ../datescanner.c tokentos.c testscanner.c > t.c
	${CC} -I.. -o $@ t.c
	rm t.c

tokentos.c: ../dateparser.h tokentos.awk
	cat ../dateparser.h | awk -f tokentos.awk > t.c
	mv t.c $@

clean:
	rm -f *.o
	rm -f testscanner
	rm -f y.tab.c
