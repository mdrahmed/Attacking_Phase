#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>

int is_DIN() {
    printf("Intercepted is_DIN() function called\n");
    return 1;  // Change the return value to the desired value
}

int (*original_is_DIN)() = NULL;

int intercepted_is_DIN() {
    printf("Intercepted is_DIN() function called\n");
    return is_DIN();
}

void __attribute__((constructor)) init() {
    printf("Interceptor initialized\n");
    
    original_is_DIN = dlsym(RTLD_NEXT, "is_DIN");
    if (original_is_DIN == NULL) {
        fprintf(stderr, "Failed to obtain original is_DIN() function pointer\n");
    } else {
        *original_is_DIN = intercepted_is_DIN;
    }
}

