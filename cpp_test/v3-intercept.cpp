#include <iostream>
using namespace std;

bool intercepted_isConditionFalse() {
    cout << "Intercepted isConditionFalse() function" << endl;
    return true;
}

bool isConditionFalse() {
    return intercepted_isConditionFalse();
}

extern "C" void __attribute__((constructor)) init() {
    intercepted_isConditionFalse();
}

