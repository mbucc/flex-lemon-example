#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include "dateparser.h"
#include "datescanner.c"

void	*ParseAlloc(void* (*allocProc)(size_t));
void	*Parse(void*, int, const char*);
void	*ParseFree(void*, void(*freeProc)(void*));

int
main(int argc, char** argv) {
	yyscan_t	scanner;
	int		lexCode;
	void		*dateParser;
	
	// Set up the scanner
	yylex_init(&scanner);
	yyset_in(stdin, scanner);
	
	// Set up the parser
	dateParser = ParseAlloc(malloc);

	while ( (lexCode = yylex(scanner)) > 0) {
		lexCode = yylex(scanner);
		printf("\nlexCode=%d\t", lexCode);
		Parse(dateParser, lexCode, yyget_text(scanner));
		if (lexCode == NEWLINE)
			Parse(dateParser, 0, NULL);
	}

	if (-1 == lexCode)
		errx(1, "The scanner encountered an error.");
	
	return 0;

}

