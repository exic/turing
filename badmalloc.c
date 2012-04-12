#include "mymalloc.h"

void* mymalloc(size_t size) {
    printf("hi, this is bad malloc. %i, %i\n", malloccount, wantedmalloccount);
    if (malloccount == wantedmalloccount) {
        return 0;
    }
    malloccount++;
    return malloc(size);
};
