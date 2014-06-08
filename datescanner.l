%{
    #include <err.h>
    #include "dateparser.h"
%}

%option reentrant
%option noyywrap  

%%


[1-9][0-9]*			{ return INT; }

[/-]					{ return SEP; }

\n					{ /* ignore */  }
[ \t]					{ /* ignore */  }

.					{ errx(1, "invalid character %s", yytext); }

%%


