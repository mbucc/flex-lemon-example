%{
    #include <err.h>
    #include "dateparser.h"
%}

%option reentrant
%option noyywrap  

%%


.+					{ return DATE_EXPR; }
.					{ errx(1, "invalid character %s", yytext); }

\n					{ /* ignore */  }
[ \t]					{ /* ignore */  }
%%


