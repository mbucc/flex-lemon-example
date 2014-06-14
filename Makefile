CFLAGS := $(CFLAGS) -std=c99
LEX=/usr/bin/lex
CC=/usr/bin/cc

all: driver date

driver: drivermain.c dateparser.c
	cat dateparser.c drivermain.c > t.c
	${CC} -o $@ t.c
	rm t.c

date: main.o dateparser.o tokenizer.o
	${CC} -o date main.o dateparser.o tokenizer.o

main.o: main.c dateparser.c tokenizer.c

# Don't use dateparser.h as a target, as the timestamp is not updated by
# lemon if there is no change in tokens. Using dateparser.c is
# sufficient, becase generating .c always generates .h
dateparser.c: dateparser.y lemon
	./lemon dateparser.y


# Prevent yacc from trying to build parsers.
# http://stackoverflow.com/a/5395195/79202
%.c: %.y

lemon: lemon.c
	${CC} -o lemon lemon.c

test: tokenizer.c
	(cd regress ; make )


.PHONY: clean
clean:
	rm -f *.o
	rm -f *.out
	rm -f tokenizer.c tokenizer.h
	rm -f dateparser.c dateparser.h
	rm -f date lemon driver
	(cd regress ; make clean)
