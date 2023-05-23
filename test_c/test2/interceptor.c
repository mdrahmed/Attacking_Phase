#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>

int is_DIN() {
    return 0;  // Original implementation, always returns 0
}

int replaced_is_DIN() {
    printf("Interceptor is_DIN()\n");
    return 1;  // Replace the return value with the desired value
}

int (*original_is_DIN)();

int is_DIN_hook() {
    if (original_is_DIN == NULL) {
        original_is_DIN = dlsym(RTLD_NEXT, "is_DIN");
    }
    return replaced_is_DIN();
}

