#include <stdio.h>

int intercepted_foo() {
    printf("Intercepted foo() function\n");
    return 1;
}

int foo() {
    return intercepted_foo();
}

void __attribute__((constructor)) init() {
    intercepted_foo();
}

