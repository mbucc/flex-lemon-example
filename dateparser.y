%include {
#include <stdio.h>
#include <assert.h>
}

%token_type 		{ const char* }
%syntax_error		{ fprintf(stderr, "Error parsing command\n"); }

main		::= INT(A) SEP INT SEP INT.	{ printf("month=%s, day=%s, year=%s\n", A, B, C); }

