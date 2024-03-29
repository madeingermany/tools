/*
 * Copyright (C) 2011 Christian Jahn. All rights reserved.
 *
 * @(#)esc2.c
 *
 */
/*
 * $ ./esc2 'a\\\$b$c\%d\\%e&f\&';
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

int
main(int argc, char *argv[])
{
	int esc = 0;

	if (argc < 2) {
		fprintf(stderr,
		    "usage: esc string\n");
		exit(1);
		/* NOTREACHED */
	}
	argv++; /* skip program name */

	while (**argv != '\0') {
		switch (**argv) {
		case '$':
		case '%':
		case '&':
			printf("esc: %c is %sescaped\n",
			    **argv, esc ? "" : "NOT ");
			break;
		case '\\':
			esc = !esc;
			break;
		default:
			esc = 0;
		}
		(*argv)++;
	} 

	return 0;
}
