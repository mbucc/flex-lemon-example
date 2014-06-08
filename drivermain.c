

/* Driver the parser without using Flex. */

#include <stdlib.h>
#include "dateparser.h"

int
main(int argc, char** argv)
{
	void		*p;
	
	/* Create the parser, passing in a pointer to the subroutine used to allocate memory.  */
	p = ParseAlloc(malloc);

	/* Feed the parser a token and then a NULL (to signal parsing is done). */
	puts("Parse1");
	Parse(p, NEWLINE, 0);
	Parse(p, 0, 0);

	/* Feed a different token. */
	puts("\nParse2");
	Parse(p, DATE_EXPR, "testing");
	Parse(p, 0, 0);

	puts("\nParse2");
	Parse(p, DATE_EXPR, "testing");
	Parse(p, NEWLINE, 0);
	Parse(p, 0, 0);

	return 0;
}

