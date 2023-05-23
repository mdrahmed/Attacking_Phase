// changing the struct value
#include <stdio.h>

typedef struct {
    int value;
} DataStruct;

void printValue(DataStruct* structPtr) {
    printf("Intercepted printValue() function called\n");
    structPtr->value = 100;  // Change the value of the struct
}

void __attribute__((constructor)) init() {
    printf("Interceptor initialized\n");
    DataStruct* myStruct = dlsym(RTLD_NEXT, "myStruct");
    printValue(myStruct);
}

