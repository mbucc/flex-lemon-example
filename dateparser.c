/* 
 *  Copyright (c) June 2014 Mark Bucciarelli <mkbucc@gmail.com>. Amherst, MA.
 *  All rights reserved. 
 * 
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 
 *  THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 *  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 *  OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 *  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 *  SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dategrammar.h"

struct token {
	char		*str;
	size_t	len;
	int		id; };

static const struct token tokens[] = {
	{"january", 7, TOK_MONTH},
	{"february", 8, TOK_MONTH},
	{"march", 5, TOK_MONTH},
	{"april", 5, TOK_MONTH},
	{"may", 3, TOK_MONTH},
	{"june", 4, TOK_MONTH},
	{"july", 4, TOK_MONTH},
	{"august", 6, TOK_MONTH},
	{"september", 9, TOK_MONTH},
	{"october", 7, TOK_MONTH},
	{"november", 8, TOK_MONTH},
	{"december", 8, TOK_MONTH},
	{"jan.", 4, TOK_MONTH},
	{"feb.", 4, TOK_MONTH},
	{"mar.", 4, TOK_MONTH},
	{"apr.", 4, TOK_MONTH},
	{"may", 3, TOK_MONTH},
	{"jun.", 4, TOK_MONTH},
	{"jul.", 4, TOK_MONTH},
	{"aug.", 4, TOK_MONTH},
	{"sep.", 4, TOK_MONTH},
	{"oct.", 4, TOK_MONTH},
	{"nov.", 4, TOK_MONTH},
	{"dec.", 4, TOK_MONTH},
	{"jan", 3, TOK_MONTH},
	{"feb", 3, TOK_MONTH},
	{"mar", 3, TOK_MONTH},
	{"apr", 3, TOK_MONTH},
	{"may", 3, TOK_MONTH},
	{"jun", 3, TOK_MONTH},
	{"jul", 3, TOK_MONTH},
	{"aug", 3, TOK_MONTH},
	{"sep", 3, TOK_MONTH},
	{"oct", 3, TOK_MONTH},
	{"nov", 3, TOK_MONTH},
	{"dec", 3, TOK_MONTH},
	
	{"and", 3, TOK_AND},
	{"at", 2, TOK_AT},

	{"a.m.", 4, TOK_AM},
	{"am", 2, TOK_AM},
	{"a", 1, TOK_AM},
	{"p.m.", 4, TOK_PM},
	{"pm", 2, TOK_PM},
	{"p", 1, TOK_PM},

	{"midnight", 8, TOK_MIDNIGHT},
	{"noon", 4, TOK_NOON},
	{"through", 7, TOK_TO},
	{"thru", 4, TOK_TO},
	{"to", 2, TOK_TO},
	
	{"@", 1, TOK_AT},
	{"-", 1, TOK_DASH},
	{"/", 1, TOK_SLASH},
	{",", 1, TOK_COMMA},
	{":", 1, TOK_COLON} };

static const int whitespace[256] = { 
	['\r']=1,
	['\n']=1,
	['\t']=1,
	[' ']=1 };


static const int digit[256] = { 
	['0']=1,
	['1']=1,
	['2']=1,
	['3']=1,
	['4']=1,
	['5']=1,
	['6']=1,
	['7']=1,
	['8']=1,
	['9']=1 };

void
lc(char **buf)
{
	char *p = *buf;
	for ( ; *p; ++p)
		*p = tolower(*p);
}

int 
tok(char **c, size_t *bsz, size_t *toksz, int *col) {
	int		i;

	/* Skip leading whitespace. */
	while( *bsz && whitespace[ (int) **c] ) {
		(*col)++; 
		(*bsz)--; 
		(*c)++; 
	}
	if (*bsz == 0) 
		return 0; // end of input

	/* Identity literal keywords. */
	for ( i = 0; i < sizeof(tokens) / sizeof(*tokens); i++ ) {	
		 if (*bsz < tokens[i].len) 
			continue;
		 if (memcmp(*c, tokens[i].str, tokens[i].len) ) 
			continue;
		 *toksz = tokens[i].len;
		 return tokens[i].id;
	}

	/* Integers  */
	*toksz=0;
	if ( (*toksz < *bsz) && digit[ (int) *(*c + *toksz) ] ) {
		while ( (*toksz < *bsz) && digit[ (int) *(*c + *toksz) ] )
			(*toksz)++;
		return TOK_INT; 
	}


	return -1;

}


int
isadate(const char *s, int *col)
{
	void		*parser  = NULL;
	char		*buf = NULL, *p, *tokentext;
	int		token, rval;
	size_t	tokensz, bufsz;

	rval = 0;

	parser = ParseAlloc(malloc);
	if (!parser)
		errx(1, "couldn't malloc Parser");

	/* Make a copy of input string, then lower case it. */
	buf = strdup(s);
	if (buf == NULL)
		errx(1, "strdup failed");

	lc(&buf);

	bufsz = strlen(buf);
	first = 1;
	p = buf;

	while ( (token = tok(&p, &bufsz, &tokensz)) > 0 ) { 
		text = strndup(p, tokensz);
		if (!tokentext)
			errx(1, "failed to strdup token");
		Parse(parser, token, tokentext);
 		bufsz -= tokensz;
		p += tokensz;
	}
	Parse(parser, 0, 0);

	if (token < 0) {
		*col = strlen( buf) - bufsz;
		rval = 1;
	}

	free(buf);
	ParseFree(parser);

	return rval;
}