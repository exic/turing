#include <stdio.h>
#include <stdlib.h>

#ifndef _MALLOCTEST
#define _MALLOCTEST

int malloccount;
int wantedmalloccount;

void* mymalloc(size_t size);

#endif
