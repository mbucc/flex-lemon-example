%{
    #include <err.h>
    #include "dateparser.h"
%}

%option reentrant
%option noyywrap

jan		[Jj][Aa][Nn](\.|[uU][aA][rR][yY])?
feb		[Ff][Ee][Bb]](\.|[rR][uU][aA][rR][yY])?
mar		[Mm][Aa][Rr](\.|[Cc][Hh])?
apr		[Ap][Pp][Rr](\.|[Ii][Ll])?
may		[Mm][Aa][Yy]
jun		[Jj][Uu][Nn](\.|[Ee])?
jul		[Jj][Uu][Ll](\.|[Yy])?
aug		[Aa][Uu][Gg](\.|[Uu][Ss][Tt])?
sep		[Ss][Ee][Pp](\.|[Tt][Ee][Mm][Bb][Ee][Rr])?
oct		[Oo][Cc][Tt](\.|[Oo][Bb][Ee][Rr])?
nov		[Nn][Oo][Vv](\.|[Ee][Mm][Bb][Ee][Rr])?
dec		[Dd][Ee][Cc](\.|[Ee][Mm][Bb][Ee][Rr])?

am		([aA][mM]|[aA])\.?
pm		([pP][mM]|[pP])\.?



%%

{am}						{ return AM; }
{pm}						{ return PM; }

:						{ return COLON; }
,						{ return COMMA; }

[nN][oO][oO][nN]			{ return NOON; }
[mM][iI][dD][nN][iI][gG][hH][tT]	{ return MIDNIGHT; }

[1-9][0-9]*				{ return INT; }

@|at						{ return AT; }

and						{ return AND; }
&						{ return AND; }


[/-]						{ return SEP; }

{jan}|{feb}|{mar}|{apr}|{may}|{jun}|{jul}|{aug}|{sep}|{oct}|{nov}|{dec}	{return MONTH;}


\n					{ /* ignore */  }
[ \t]					{ /* ignore */  }

.					{ errx(1, "invalid character %s", yytext); }

%%


