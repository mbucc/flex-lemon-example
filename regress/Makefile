CFLAGS := $(CFLAGS) -std=c99

test: test_tokenizer test_tokenizer.sh
	./test_tokenizer.sh

test_tokenizer: ../tokenizer.c tokentos.c test_tokenizer.c
	cat ../tokenizer.c tokentos.c test_tokenizer.c > t.c
	${CC} -I.. -o $@ t.c
	rm t.c

tokentos.c: ../dateparser.h tokentos.awk
	cat ../dateparser.h | awk -f tokentos.awk > t.c
	mv t.c $@

clean:
	rm -f *.o
	rm -f test_tokenizer
	rm -f y.tab.c
	rm -f tokentos.c
