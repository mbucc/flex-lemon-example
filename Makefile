CFLAGS := $(CFLAGS) -std=c99

date: main.o dateparser.o datescanner.o
	$(CC) -o date main.o dateparser.o datescanner.o

main.o: main.c dateparser.h datescanner.h

dateparser.o: dateparser.h dateparser.c

dateparser.h dateparser.c: dateparser.y lemon
	./lemon dateparser.y

datescanner.o: datescanner.h

datescanner.h: datescanner.l
	flex --outfile=datescanner.c --header-file=datescanner.h datescanner.l

# Prevent yacc from trying to build parsers.
# http://stackoverflow.com/a/5395195/79202
%.c: %.y

lemon: lemon.c
	$(CC) -o lemon lemon.c

.PHONY: clean
clean:
	rm -f *.o
	rm -f datescanner.c datescanner.h
	rm -f dateparser.c dateparser.h dateparser.out
	rm -f date lemon
