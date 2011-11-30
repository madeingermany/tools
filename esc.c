/*
 * Copyright (C) 2011 Christian Jahn. All rights reserved.
 *
 * @(#)esc.c
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int
isesc(const char *path, size_t size)
{
#ifdef RECURSIVE
	if (size > 0
	    && path[-1] == '\\')
		return !isesc(&path[-1], size - 1);
	return 0;
#else
	int off = 1;
	while (size-- > 0
	    && path[-off] == '\\')
		off++;
	return !(off % 2);
#endif /* RECURSIVE */
}

int
main(int argc, char *argv[])
{
	char *slash;

	if (argc < 2) {
		fprintf(stderr,
		    "usage: esc path\n");
		exit(1);
	}
	++argv; /* skip program name */

	slash = strchr(*argv, '/');
	if (slash == NULL) {
		fprintf(stderr,
		    "esc: path must contain at least one /.\n");
		exit(1);
	}

	printf("%s is %sescaped.\n",
	    *argv, isesc(slash, slash - *argv) ? "" : "NOT ");

	return 0;
}
