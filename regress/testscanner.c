#include <err.h>


const char *
tokentos(int token)
{
	switch (token) {
	case 1: return "NEWLINE"; break;
	case 2: return "DATE_EXPR"; break;
	default: errx(1, "unexpected token %d", token); break;
	}
}

int
main(int argc, char **argv)
{
	int	token;
	void	*p;

	yylex_init(&p);

	while ( (token = yylex(p)) > 0 ) 
		printf("%s ", tokentos(token));

	yylex_destroy(p);

	return 0;
}