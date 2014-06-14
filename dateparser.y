%include {
#include <stdio.h>
#include <assert.h>
}

%token_type 		{ const char* }
%syntax_error		{ fprintf(stderr, "Error parsing command\n"); }

main			::= date_expr.

date_expr		::= date_range AT times.
date_expr		::= date AT times.
date_expr		::= date.

date_range	::= date TO date.
date_range	::= date DASH date.

date			::= INT date_sep INT date_sep INT.
date			::= MONTH INT INT.
date_sep		::= DASH.
date_sep		::= SLASH.

times		::= times AND time.
times		::= times COMMA time.
times		::= time.

time			::= INT meridian.
time			::= INT COLON INT meridian.
time			::= NOON.
time			::= MIDNIGHT.

meridian		::= AM.
meridian		::= PM.


