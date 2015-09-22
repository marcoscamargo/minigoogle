#include "minigoogle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sinfo {
	int code;
	char name[51];
	int relevance
	char link[101];
	char *keyword[51];
};

struct no {
	Site *key;
	struct no *next;
	struct no *previous;
};

struct google {
	No *beg;
	No *end;

	int tam;
};