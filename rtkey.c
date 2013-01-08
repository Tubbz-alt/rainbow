#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "rainbow.h"

static void usage(int argc, char** argv)
{
	(void) argc;

	fprintf(stderr,
		"Usage: %s l_min l_max n\n"
		"compute the n-th string of the keyspace\n"
		"\n"
		"l_min  minimum key length\n"
		"l_max  maximum key length\n"
		"n      key index\n"
		,
		argv[0]
	);
}

int main(int argc, char** argv)
{
	if (argc == 1 || strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)
	{
		usage(argc, argv);
		exit(0);
	}
	else if (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0)
	{
		printf("rtkey\n");
		printf("Compiled on %s at %s\n", __DATE__, __TIME__);
		exit(0);
	}

	if (argc < 4)
	{
		usage(argc, argv);
		exit(1);
	}

	const u32   l_min     = atol(argv[1]);
	const u32   l_max     = atol(argv[2]);
	const char* charset   = "0123456789abcdefghijklmnopqrstuvwxyz";
	const u32   n_charset = strlen(charset);
	const u64   index     = atoll(argv[3]);

	char* string = malloc(l_max+1);
	assert(string);
	string[l_max] = 0;

	if (index2key(index, string, l_min, l_max, charset, n_charset))
		printf("key no %llu = '%s'\n", index, string);
	else
		printf("key out of range\n");

	free(string);
	return 0;
}
