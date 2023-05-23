#include <stdio.h>

extern "C" int intercepted_foo() {
    printf("Intercepted foo() function\n");
    return 1;
}

extern "C" int foo() {
    return intercepted_foo();
}

void __attribute__((constructor)) init() {
    foo();
}

