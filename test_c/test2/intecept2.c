#include <stdio.h>

int intercepted_is_DIN() {
    printf("Intercepted is_DIN() function called\n");
    return 1;  // Change the return value to the desired value
}

int is_DIN() __attribute__((weak, alias("intercepted_is_DIN")));

void __attribute__((constructor)) init() {
    printf("Interceptor initialized\n");
}

