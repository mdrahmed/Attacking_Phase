#include <stdio.h>

void foo() {
    printf("Intercepted foo() function\n");
}

void __attribute__((constructor)) init() {
    foo();
}

