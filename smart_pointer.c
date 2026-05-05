#include <stdlib.h>

int* allocate (size_t x) {
    int *ptr = (int*)calloc(x, sizeof(int));

    if (ptr == NULL) {
        return NULL;
    }
    
    return ptr;
}

void release(int* x) {
    free(x);
}
