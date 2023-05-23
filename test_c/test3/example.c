#include <stdio.h>

typedef struct {
    int value;
} DataStruct;

DataStruct myStruct;

void printValue() {
    printf("Value: %d\n", myStruct.value);
}

int main() {
    myStruct.value = 42;
    printValue();
    return 0;
}

