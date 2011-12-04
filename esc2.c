/*
 * Copyright (C) 2011 Christian Jahn. All rights reserved.
 *
 * @(#)esc.c
 *
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
	}
	argv++; /* skip program name */

	while (**argv != '\0') {
		switch (**argv) {
		case '\\':
			esc = !esc;
			break;
		case '$':
		case '%':
		case '&':
			printf("esc: %c is %sescaped\n",
			    **argv, esc ? "" : "NOT ");
			break;
		default:
			esc = 0;
		}
		(*argv)++;
	} 
	return 0;
}
