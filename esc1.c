/*
 * Copyright (C) 2011 Christian Jahn. All rights reserved.
 *
 * @(#)esc1.c
 *
 */
/*
 * $ ./esc1 'a\\\$b$c\%d\\%e&f\&';
 * esc: $ is escaped
 * esc: $ is NOT escaped
 * esc: % is escaped
 * esc: % is NOT escaped
 * esc: & is NOT escaped
 * esc: & is escaped
 * $
 */

#include <stdio.h>
#include <stdlib.h>

static int
isesc(const char *arg, size_t size)
{
#ifdef RECURSIVE
	if (size > 0
	    && arg[-1] == '\\')
		return !isesc(&arg[-1], size - 1);
	return 0;
#else
	int off = 0;
	while (off++ < size
	    && arg[-off] == '\\')
		; /* nothing */
	return off % 2 == 0;
#endif /* RECURSIVE */
}

int
main(int argc, char *argv[])
{
	char *arg;

	if (argc < 2) {
		fprintf(stderr,
		    "usage: esc string\n");
		exit(1);
		/* NOTREACHED */
	}
	arg = *++argv; /* skip program name */

	while (*arg != '\0') {
		switch (*arg) {
		case '$':
		case '%':
		case '&':
			printf("esc: %c is %sescaped\n",
			    *arg, isesc(arg, arg - *argv) ? "" : "NOT ");
		}
		arg++;
	} 

	return 0;
}
