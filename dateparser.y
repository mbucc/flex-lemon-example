%include {
#include <stdio.h>
#include <assert.h>
}

%token_type 		{ const char* }
%syntax_error		{ fprintf(stderr, "Error parsing command\n"); }

main		::= date TO date AT times.

main		::= date DASH date AT times.

main		::= date AT times.
main		::= date AT time.
main		::= date.

date		::= INT date_sep INT date_sep INT.
date		::= MONTH INT INT.

times	::= times AND time.
times	::= times COMMA time.

time		::= INT meridian.
time		::= INT COLON INT meridian.
time		::= NOON.
time		::= MIDNIGHT.

date_sep	::= DASH.
date_sep	::= SLASH.
meridian	::= AM.
meridian	::= PM.

