#include <stdio.h>

bool intercepted_isConditionFalse() {
    printf("Intercepted isConditionFalse() function\n");
    return true;  // Change the condition to true
}

bool isConditionFalse() {
    return intercepted_isConditionFalse();
}

void __attribute__((constructor)) init() {
    intercepted_isConditionFalse();
}

