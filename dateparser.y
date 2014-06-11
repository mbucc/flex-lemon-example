%include {
#include <stdio.h>
#include <assert.h>
}

%token_type 		{ const char* }
%syntax_error		{ fprintf(stderr, "Error parsing command\n"); }

main		::= date AT time AND time.
main		::= date AT time.
main		::= date.

date		::= INT(A) SEP INT(B) SEP INT(C).	{ printf("month=%s, day=%s, year=%s\n", A, B, C); }
date		::= MONTH(A) INT(B) INT(C).		{ printf("month=%s, day=%s, year=%s\n", A, B, C); }

time		::= INT meridian.
time		::= INT COLON INT meridian.

meridian	::= AM.
meridian	::= PM.

