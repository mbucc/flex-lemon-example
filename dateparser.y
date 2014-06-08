%include {
#include <stdio.h>
#include <assert.h>
}

%token_type 		{ const char* }
%syntax_error		{ fprintf(stderr, "Error parsing command\n"); }

main		::= NEWLINE.				{ puts("NEWLINE"); }
main		::= DATE_EXPR(A).			{ printf("DATE_EXPR: %s\n", A); }
main		::= DATE_EXPR(A) NEWLINE.	{ printf("DATE_EXPR: %s, then NEWLINE\n", A); }
